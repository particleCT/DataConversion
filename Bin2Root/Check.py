import glob
from ROOT import *
import sys

ROOTList = glob.glob(sys.argv[1]+"*.root")
for rootfile in ROOTList:
    f=TFile(rootfile)
    phase = f.Get("phase")
    branchesname =[x.GetName() for x in phase.GetListOfBranches()]
    if(not "WET_prob" in branchesname): print rootfile
