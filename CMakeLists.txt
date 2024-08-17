# Set the minimum required version of cmake for this project
cmake_minimum_required(VERSION 3.22.1)

# Define the C++ standard whose features we request to build this project
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the project name with the corresponding version
project(xc1SaveEditor VERSION 0.1.0)

# Add an executable to our project
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/SaveFile.cpp
    src/DataObject.cpp
    src/ArrayObject.cpp
    src/Types.cpp
)

# Add the include header files to our target
target_include_directories(${PROJECT_NAME} PRIVATE include)

#include googletest
enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/ff233bdd4cac0a0bf6e5cd45bda3406814cb2796.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)
add_executable(tests
    tests.cc
)
target_link_libraries(
    tests
    GTest::gtest_main
)
add_test(tests test1)
