import os,glob, sys
import random

FileList = glob.glob(sys.argv[1]+"*.bin")
nJob = len(FileList)/8 
OutFolder = sys.argv[2]
for job in range(nJob):
    print job
    f=open("submit_temp.sh")
    f2=open("submit.sh","w")
    for lines in f.readlines():        
        if(lines.count("$COMMANDLINE")):
            for File in FileList[8*job:8*(job+1)]:
                LaunchFile = "/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root "
                command = LaunchFile + File  + " " +OutFolder
                f2.write(command+" &\n")
                print command
        else:
            f2.write(lines)
    f.close()
    f2.close()
    os.system("qsub -l nodes=2:ppn=8 submit.sh")
    
