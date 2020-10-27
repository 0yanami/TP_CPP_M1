set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB TEST_SOURCES *.cpp)

set(SOURCES ${TEST_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY} "main.cpp")

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)