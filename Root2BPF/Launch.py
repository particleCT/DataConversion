import os,glob, sys
import random

FileList = glob.glob(sys.argv[1]+"*.root")
nJob = len(FileList)/16 

for job in range(nJob):
    print job
    f=open("submit_temp.sh")
    f2=open("submit.sh","w")
    for lines in f.readlines():        
        if(lines.count("$COMMANDLINE")):
            for File in FileList[16*job:16*(job+1)]:
                LaunchFile = "/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF "
                command = LaunchFile + File
                f2.write(command+" &\n")
                print command
        else:
            f2.write(lines)
    f.close()
    f2.close()
    os.system("qsub -l nodes=2:ppn=16 submit.sh")












