cmake_minimum_required(VERSION  3.10)
project("calculator")

# These two lines define the C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

# Set compile option for the project
set(CMAKE_CXX_FLAGS"${CMAKE_CXX_FLAGS} -Wall -Werror -g -ggdb -D ")


set(gtest_force_shared_crt 1 CACHE BOOL "")
add_subdirectory(lib/googletest-release-1.10.0)

add_subdirectory(src)
add_subdirectory(test)