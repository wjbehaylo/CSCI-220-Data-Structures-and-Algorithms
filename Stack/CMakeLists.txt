# CMakeLists.txt for the stack project

# This file will create a Makefile with several targets,
# enabling you to test your code for each of the 3 stages
# of the project.  The targets include:
#
# stage1 - builds the programs run-stage1-tests and run-stage1-main
# stage2 - builds the programs run-stage2-tests and run-stage3-main
# stage3 - builds the programs run-stage3-tests and run-stage3-main
#
# The stage 1 programs depend on your code in stack-stage1.h and
# stack-stage1.cpp.
#
# Because a working stage3 implementation will pass all of the stage2
# tests, there is no stage2.h - just a stage3.h.  So the stage 2 and
# stage 3 targets all depend on stage3.h.
#
# E.g., to do stage 2 of the project, edit the file stage3.h and then
# in the terminal issue the commands:
# cmake .   -- you only have to do this once, unless something goes wrong
# make stage2
# ./run-stage2-tests  -- for linux and Mac, or Windows with WSL
# run-stage2-tests    -- for native Windows
#
# You can also write your own custom testing code in main-stage1.cpp or
# main-stage3.cpp and run the code using 
# ./run-stage1-main
# or
# ./run-stage3-main

cmake_minimum_required(VERSION 3.14)

# Ensure we can use gdb
set(CMAKE_BUILD_TYPE Debug)

project(project1-stack)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

# Retrieve the googletest test framework
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_compile_options(-pedantic -Wall -Wextra)

add_executable(run-stage1-main stack-stage1.h stack-stage1.cpp main-stage1.cpp)
add_executable(run-stage3-main stack-stage3.h main-stage3.cpp)

add_executable(
  run-stage1-tests EXCLUDE_FROM_ALL
  stack-stage1.h
  stack-stage1.cpp
  stage1-tests/stage1-tests.cpp
  )

add_executable(
  run-stage2-tests EXCLUDE_FROM_ALL
  stack-stage3.h
  stage2-3-tests/stage2-tests-string.cpp 
  stage2-3-tests/stage2-tests-other-types.cpp 
  )

add_executable(
  run-stage3-tests EXCLUDE_FROM_ALL
  stack-stage3.h
  stage2-3-tests/stage2-tests-string.cpp 
  stage2-3-tests/stage2-tests-other-types.cpp 
  stage2-3-tests/stage3-tests.cpp
  )

target_link_libraries(
  run-stage1-tests GTest::gtest_main
)

target_link_libraries(
  run-stage2-tests GTest::gtest_main
)

target_link_libraries(
  run-stage3-tests GTest::gtest_main
)

# some convenience targets
add_custom_target(stage1)
add_custom_target(stage2)
add_custom_target(stage3)
add_dependencies(stage1 run-stage1-tests run-stage1-main)
add_dependencies(stage2 run-stage2-tests run-stage3-main)
add_dependencies(stage3 run-stage3-tests run-stage3-main)
