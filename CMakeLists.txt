cmake_minimum_required(VERSION  3.17.0)
project("calculator")

# These two lines define the C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

# Set compile option for the project
set(CMAKE_CXX_FLAGS"${CMAKE_CXX_FLAGS} -Wall -Werror -g -ggdb")

include_directories(include/)
file(GLOB PROJECT_SOURCES src/*.cpp)
# Configure the executable target from the source files
add_executable(calculator ${PROJECT_SOURCES} "src/main.cpp")