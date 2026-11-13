cmake_minimum_required(VERSION 3.21.0)
project(LuLaFiTh LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LULAFITH_KOKKOS_VERSION "5.1.1" CACHE STRING "Kokkos version tag or commit hash")

include(FetchContent)
FetchContent_Declare(
	Kokkos
	GIT_REPOSITORY https://github.com/kokkos/kokkos.git
	GIT_TAG ${LULAFITH_KOKKOS_VERSION}
	FIND_PACKAGE_ARGS NAMES Kokkos::kokkos
)
FetchContent_MakeAvailable(Kokkos)


add_executable(test src/main.cpp)
target_link_libraries(test Kokkos::kokkos)


