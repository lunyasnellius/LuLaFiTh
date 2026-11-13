

#if [ -d build ]; then 
#	rm -r build
#fi 

mkdir -p build 
cd build

cmake ../LuLaFiTh

cmake --build .


