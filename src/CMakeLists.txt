
# These two lines define the C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

# Set compile option for the project
set(CMAKE_CXX_FLAGS"${CMAKE_CXX_FLAGS} -Wall -Werror -g -ggdb -D ")


include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES *.cpp)

# Configure the executable target from the source files
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES} "main.cpp")

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})