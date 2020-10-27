include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES *.cpp)

# Configure the executable target from the source files
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES} "main.cpp")

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})