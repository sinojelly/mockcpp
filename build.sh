#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

# $1  --- compiler name  (GNU)
# $2  --- [optional] compiler major version  (The first part of cxx compiler version)

# fast fail
set -e

. "tools/build_functions.sh"

MY_OS_NAME=""
MY_CXX_COMPILER_NAME=""
MY_CXX_COMPILER_MAJOR_VERSION=""
CMAKE_COMPILER_PARAM=""
MAKE_BUILD_TYPE=""

AUTO_CXX_VER=`gcc -dumpversion | awk -F.  '{print $1}'`
InitEnviroment $1 $AUTO_CXX_VER

BUILD_DIR="build_$MY_CXX_COMPILER_NAME"

OS_COMPILER="$MY_OS_NAME/$MY_CXX_COMPILER_NAME/$MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER in Shell : $OS_COMPILER"

cmake  -S . -B $BUILD_DIR/mockcpp
cmake  -S tests/3rdparty/testngpp -B $BUILD_DIR/mockcpp_testngpp
cmake  -S tests -B $BUILD_DIR/mockcpp_tests

CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp
CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp_testngpp
CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp_tests

RunTestsFromPrebuiltTools $BUILD_DIR ut $MAKE_BUILD_TYPE $OS_COMPILER
