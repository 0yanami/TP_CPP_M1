include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES *.cpp)

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES} "main.cpp")

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})