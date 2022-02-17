import subprocess
import re
import os
import json
from tqdm import tqdm

class SingleTrial:

    def __init__(self, **kwargs):
        params = {"num_proc": 2, "path_to_genome" : "../../data/EscherichiaColi/genome.fna", "over":False, "gene_index":2}
        params.update(kwargs)
        

        self.genes = params["path_to_genome"].replace("genome.fna", "genes.fna")
        with open(self.genes, "r") as f:
            s = f.read()
        self.genes = re.split(">.*\n", s)

        with open("../../data/pat.txt", "w+") as f:
            f.write(self.genes[params["gene_index"]])


        if params["num_proc"] == 1:
            process = subprocess.Popen(['./serial.sh', params["path_to_genome"]], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = process.communicate()  
        else:
            process = subprocess.Popen(['./scalability.sh', str(params["num_proc"])+ ("  --oversubscribe" if params["over"] else ""), params["path_to_genome"]], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = process.communicate()       

        
        lines = str(stdout).split("\\n")

        self.all_results = {}

        first = re.compile("size of the full text: (\\d+) and the size of the pattern: (\\d+)")
        second = re.compile("Slave of rank: (\\d+) subtext hash: (\\d+) length of the string: (\\d+)")
        third = re.compile("Found: (\\d+) occurences in (\\d+\.\\d+) milliseconds.")
        
        for line in lines:

            try:
                result = first.search(line)
                self.all_results["text_size"] = int(result.group(1))
                self.all_results["pattern_size"] = int(result.group(2))
            except:
                pass

            try:
                result = third.search(line)
                self.all_results["num_occurances"] = int(result.group(1))
                self.all_results["millisecs"] = float(result.group(2))
            except:
                pass

            try:
                result = second.search(line)
                self.all_results["subtext_size"] = int(result.group(3))
            except:
                pass



os.system("mpic++ -std=c++11 ../parallel/main.cpp")


gene_indeces = [2, 40, 1234]

results_list = []


# e coli
for i in tqdm(range(1,9)):
    
    for g in gene_indeces:
        res = SingleTrial(num_proc=i, gene_index=g).all_results
        res["genome"] = "e_coli"
        res["gene_index"] = g
        res["num_cores"] = i
        results_list.append(res)


# nostoc punctiforme
for i in tqdm(range(1,9)):
    for g in gene_indeces:
        res = SingleTrial(num_proc=i, gene_index=g, path_to_genome="../../data/NostocPunctiforme/genome.fna").all_results
        res["genome"] = "nostoc"
        res["gene_index"] = g
        res["num_cores"] = i
        results_list.append(res)


with open("../../presentation/test_results.txt", "w+") as f:
    f.write(json.dumps(results_list))


os.system("rm a.out")




