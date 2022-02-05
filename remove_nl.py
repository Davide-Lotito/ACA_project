import sys
import os

def __main__():

    if len(sys.argv)!=2 or not os.path.isfile(sys.argv[1]):
        print(100*"*", "\n", "USAGE of 'remove_nl.py':", "\n", "python3 remove_nl.py path/to/myfile.txt", "\n", "Creates a new file in the same dir named 'myfile_no_new_lines.txt', totally devoid of \\n chars.", "\n", 100*"*")
        exit()
    
    with open(sys.argv[1], "r") as f:
        s = f.read().replace("\n", "")
            
    with open(sys.argv[1].split("/")[-1].split(".")[0]+"_no_new_lines.txt", "w+") as f:
        f.write(s)
  
    

if __name__ == "__main__":
    __main__()