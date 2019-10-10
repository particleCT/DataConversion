#!/bin/sh
#PBS -N binary
#PBS -e output.err
#PBS -o output.out
source /home/cacfek/.bashrc
cd /ion/home/hect/DataConversion/Root2DROPTVS
/ion/home/hect/DataConversion/Root2DROPTVS/bin/Root2DROPTVS ../Bin2Root/Data/projection_255.5.root &
/ion/home/hect/DataConversion/Root2DROPTVS/bin/Root2DROPTVS ../Bin2Root/Data/projection_136.5.root &
/ion/home/hect/DataConversion/Root2DROPTVS/bin/Root2DROPTVS ../Bin2Root/Data/projection_29.5.root &
/ion/home/hect/DataConversion/Root2DROPTVS/bin/Root2DROPTVS ../Bin2Root/Data/projection_15.0.root &
/ion/home/hect/DataConversion/Root2DROPTVS/bin/Root2DROPTVS ../Bin2Root/Data/projection_346.5.root &
/ion/home/hect/DataConversion/Root2DROPTVS/bin/Root2DROPTVS ../Bin2Root/Data/projection_201.5.root &
/ion/home/hect/DataConversion/Root2DROPTVS/bin/Root2DROPTVS ../Bin2Root/Data/projection_163.0.root &
/ion/home/hect/DataConversion/Root2DROPTVS/bin/Root2DROPTVS ../Bin2Root/Data/projection_39.0.root &

wait
