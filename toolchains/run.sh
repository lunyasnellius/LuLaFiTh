

#if [ -d build ]; then 
#	rm -r build
#fi 

#mkdir -p build 
#cd build

blddir=build
srcdir="$(realpath $(dirname $0)/..)"

cmake \
  -DCMAKE_BUILD_TYPE=RELEASE \
  -DKokkos_ARCH_NATIVE=ON \
  -DKokkos_ENABLE_OPENMP=ON \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -S ${srcdir} \
  -B ${blddir} || { echo "+++++ CMake configuration failed +++++"; exit 1; }


cmake --build ${blddir} --target all -- -j 8 || { echo "+++++ CMake build failed +++++"; exit 1; }


