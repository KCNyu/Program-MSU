project(LTL_TO_AUTOMATON)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

aux_source_directory(./src SRC)
aux_source_directory(./test TEST)

include_directories(./inc)

add_executable(example ${SRC} ${TEST})

# set up the test
enable_testing()

macro(ExampleTest test_name)
    add_test(NAME test_${test_name} COMMAND ./example ${test_name})
    set_tests_properties(test_${test_name} PROPERTIES PASS_REGULAR_EXPRESSION "Test passed!")
endmacro(ExampleTest)

ExampleTest(1)
ExampleTest(2)