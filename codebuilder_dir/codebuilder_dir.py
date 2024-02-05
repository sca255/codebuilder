#dont use does not work currently if you know how to fix it fix it a nd create a pul request
import multiprocessing
import subprocess
import os
path = input("Enter the path to the directory: ")
print("Number of CPU cores: ", multiprocessing.cpu_count())
result = os.listdir(path)
try:  
    os.mkdir("output")  
except OSError as error:  
    print(error)   
def run(name):
    return subprocess.run(["./codebuilder.exe","-py",name,"output/"+name+".py"], capture_output=True, text=True)
with multiprocessing.Pool() as pool:
    j=[]
    for i in result:
       j.append(i) 
    global r
    r=pool.imap_unordered(run, j)
        
for i in r:
    print(i.stdout)
    print(i.stderr)
    print(i.returncode)