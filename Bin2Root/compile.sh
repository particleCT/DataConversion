source /ion/home/hect/Utils/root/bin/thisroot.sh
export G4WORKDIR=$PWD
#rm -rf build
mkdir build
cd build

rm -rf *

cmake -DCMAKE_INSTALL_PREFIX=$G4WORKDIR ../

make -j8

make install

cd ../
rm -rf build
#./bin/SplinePropagation 5CM/210MeV5CM.root 80
