#!/bin/sh
#PBS -N binary
#PBS -e output.err
#PBS -o output.out
source /ion/home/hect/Utils/root/bin/thisroot.sh
cd /ion/home/hect/DataConversion/Bin2Root
/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root ../../Data/CPC_2016_08_13/CIRSPHP1/inf/projection_209.0.bin ./Data/ &
/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root ../../Data/CPC_2016_08_13/CIRSPHP1/inf/projection_215.0.bin ./Data/ &
/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root ../../Data/CPC_2016_08_13/CIRSPHP1/inf/projection_101.5.bin ./Data/ &
/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root ../../Data/CPC_2016_08_13/CIRSPHP1/inf/projection_11.5.bin ./Data/ &
/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root ../../Data/CPC_2016_08_13/CIRSPHP1/inf/projection_279.0.bin ./Data/ &
/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root ../../Data/CPC_2016_08_13/CIRSPHP1/inf/projection_220.5.bin ./Data/ &
/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root ../../Data/CPC_2016_08_13/CIRSPHP1/inf/projection_225.0.bin ./Data/ &
/ion/home/hect/DataConversion/Bin2Root/bin/Bin2Root ../../Data/CPC_2016_08_13/CIRSPHP1/inf/projection_180.5.bin ./Data/ &

wait
