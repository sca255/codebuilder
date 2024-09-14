import os

def parsepattern(pattern:str ,r): #example cl$r%(v1).py:v1=$R*0.11+0.86
    pattern=pattern.replace("$R",r)
    pdb=pattern.split(":")
    vs={}
    vl=[]
    for i in pdb[1:]:
        idb = i.split("=")
        vl.append(idb[0])
        vs[idb[0]]=eval(idb[1])
        
    print(vs)
    ptr=pdb[0]
    for i in vl:
        ptr=ptr.replace(f"%({i})",str(vs[i]))
    return ptr
        
    
    
while True:
    x=input(">>")
    if x=="exit":
        break
    elif x=="cl":
        os.system("clear")
    elif x=="r":
        r=int(input("no of time to repeat"))
        P=input("pattern")
        b=input("path of source")
        l= input("lang")
        for i in range(r):
            
            #os.system(f"./codebuilder.exe {l} {b}  output/{parsepattern(P,i)}")
            print(f"./codebuilder.exe {l} {b}  output/{parsepattern(P,str(i))}")
        
        
