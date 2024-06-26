set(LIBIPC_PROJECT_DIR "${PROJECT_SOURCE_DIR}")
project(test-ipc)
cmake_minimum_required(VERSION 3.22)


add_compile_options(
    -Wno-attributes 
    -Wno-missing-field-initializers 
    -Wno-unused-variable 
    -Wno-unused-function)

include_directories(
    ${LIBIPC_PROJECT_DIR}/include 
    ${LIBIPC_PROJECT_DIR}/src
    ${LIBIPC_PROJECT_DIR}/test
    ${LIBIPC_PROJECT_DIR}/3rdparty
    ${LIBIPC_PROJECT_DIR}/3rdparty/gtest/include)

file(GLOB SRC_FILES
    ${LIBIPC_PROJECT_DIR}/test/*.cpp
    )
file(GLOB HEAD_FILES ${LIBIPC_PROJECT_DIR}/test/*.h)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEAD_FILES})


link_directories(${LIBIPC_PROJECT_DIR}/3rdparty/gperftools)
target_link_libraries(${PROJECT_NAME} gtest gtest_main ipc)
