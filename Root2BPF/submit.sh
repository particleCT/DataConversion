#!/bin/sh
#PBS -N binary
#PBS -e output.err
#PBS -o output.out
source /home/cacfek/.bashrc
cd /ion/home/hect/DataConversion/Root2BPF
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_136.0.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_55.5.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_241.0.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_355.0.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_52.5.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_95.5.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_57.0.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_323.0.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_307.0.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_308.5.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_126.5.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_273.5.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_70.5.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_214.0.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_47.0.root &
/ion/home/hect/DataConversion/Root2BPF/bin/Root2BPF ../Bin2Root/Data_Linepair/projection_60.5.root &

wait
