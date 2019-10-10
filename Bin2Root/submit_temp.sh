#!/bin/sh
#PBS -N binary
#PBS -e output.err
#PBS -o output.out
source /ion/home/hect/Utils/root/bin/thisroot.sh
cd /ion/home/hect/DataConversion/Bin2Root
$COMMANDLINE

wait
