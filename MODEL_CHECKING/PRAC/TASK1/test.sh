#!/bin/bash

clean_project() {
    rm -rf build
}

build_project() {
    cmake -B build && cmake --build build
}

run_tests() {
    cd build && ctest --verbose
}

if [ "$1" == "clean" ]; then
    clean_project
else
    clean_project
    build_project
    run_tests
fi