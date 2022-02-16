import sys
import os

usage_string =  f"""{100*"*"}\nUSAGE of 'remove_nl.py':\npython3 remove_nl.py path/to/myfile_or_my_dir\nCreates a new file: 'myfile_or_my_dir.txt', totally devoid of '\\n' chars.\nIn case a directory is given as input, the text-files it contains will be aggregated.\n{100*"*"}"""

class Colors:
    OKGREEN = '\033[92m' 
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    UNDERLINE = '\033[4m'

try: from tqdm import tqdm; wrapper = tqdm
except ModuleNotFoundError as e: wrapper = lambda x:x; print(Colors.WARNING+"tqdm not found, progress-bar not available."+Colors.ENDC); 


def chunker(seq, size):
    return (seq[pos:pos + size] for pos in range(0, len(seq), size))

def __main__():

    if len(sys.argv)!=2 :
        print(usage_string)
        exit()
    
    # get proper list (or single-element-list) of files to be concatenated 
    if os.path.isdir(sys.argv[1]):
        files = [os.path.join(sys.argv[1],f) for f in os.listdir(sys.argv[1])]
        newname = f"{sys.argv[1].split('/')[-1]}_no_new_lines.txt"
    elif os.path.isfile(sys.argv[1]):
        files = [sys.argv[1]]
        newname = f"{sys.argv[1].split('/')[-1].split('.')[0]}_no_new_lines.txt"

    else:
        print(usage_string)
        exit()
    print(f"{Colors.OKGREEN}running: remove_nl.py{Colors.ENDC}")
    
    # read and eventually concatenate
    print("reading files...")
    buffer = ""
    for f in wrapper(files):
        with open(f, "r") as f:
            buffer += f.read()
    
    # write each chunk to the file in append mode
    print("writing back...")
    CHUNK_SIZE = 100000 

    # delete file contents in case it already existed.
    with open(newname, "w+") as f:
        f.write("")

    with open( newname , "a+") as f:
        for chunk in wrapper(chunker(buffer, CHUNK_SIZE)):
            chunk = chunk.replace("\n", "") #remove any newline from each chunk
            f.write(chunk) 
    print(f"{Colors.OKGREEN}done: remove_nl.py{Colors.ENDC}")


if __name__ == "__main__":
    __main__()