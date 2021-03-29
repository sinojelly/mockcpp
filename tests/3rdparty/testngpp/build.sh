#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

# $1  --- compiler name  (GNU)
# $2  --- [optional] compiler major version  (The first part of cxx compiler version)

# fast fail
set -e

. "../../../tools/build_functions.sh"

MY_OS_NAME=""
MY_CXX_COMPILER_NAME=""
MY_CXX_COMPILER_MAJOR_VERSION=""
CMAKE_COMPILER_PARAM=""
MAKE_BUILD_TYPE=""

AUTO_COMPILER="GNU"  #  $1
AUTO_CXX_VER=`gcc -dumpversion | awk -F.  '{print $1}'`  # $2
InitEnviroment $AUTO_COMPILER $AUTO_CXX_VER

BUILD_DIR="build_$MY_CXX_COMPILER_NAME"

OS_COMPILER="$MY_OS_NAME/$MY_CXX_COMPILER_NAME/$MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER in Shell : $OS_COMPILER"

cmake  -S . -B $BUILD_DIR/testngpp
cmake  -S tests/3rdparty/testngppst -B $BUILD_DIR/testngpp_testngppst
cmake  -S tests -B $BUILD_DIR/testngpp_tests

CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp
CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp_testngppst
CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp_tests

RunTests $BUILD_DIR testngpp_tests $MAKE_BUILD_TYPE testngpp_testngppst
