#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

# $1  --- [optional] compiler name  (default is GNU)
# $2  --- [optional] compiler major version  (The first part of cxx compiler version)

# if you want to choose a compiler other than GNU, you can 
#   uncomment the ReadUserChoice, config the CompilerArray in tools/build_functions.sh, then
#   InitEnviroment $USER_CHOOSED_COMPILER $USER_CHOOSED_COMPILER_MAJOR_VER

# fast fail
set -e

. "tools/build_functions.sh"

MY_OS_NAME=""
MY_CXX_COMPILER_NAME=""
MY_CXX_COMPILER_MAJOR_VERSION=""
CMAKE_COMPILER_PARAM=""
MAKE_BUILD_TYPE=""

USER_CHOOSED_COMPILER=""
USER_CHOOSED_COMPILER_MAJOR_VER=""

# script usage 1: no parameter, use GNU compiler
AUTO_COMPILER="GNU"
AUTO_CXX_VER=`gcc -dumpversion | awk -F.  '{print $1}'`
InitEnviroment $AUTO_COMPILER $AUTO_CXX_VER

# script usage 2: input the compiler name and major version
#InitEnviroment $1 $2

# script usage 3: choose the compiler and version
#ReadUserChoice
#InitEnviroment $USER_CHOOSED_COMPILER $USER_CHOOSED_COMPILER_MAJOR_VER

BUILD_DIR="build_$MY_CXX_COMPILER_NAME"

OS_COMPILER="$MY_OS_NAME/$MY_CXX_COMPILER_NAME/$MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER in Shell : $OS_COMPILER"

#if [ $3 != "test" ]; then

cmake  -S . -B $BUILD_DIR/mockcpp
cmake  -S tests/3rdparty/testngpp -B $BUILD_DIR/mockcpp_testngpp
cmake  -S tests -B $BUILD_DIR/mockcpp_tests

CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp
CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp_testngpp
CompileProject $MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp_tests

#fi

RunTests $BUILD_DIR mockcpp_tests $MAKE_BUILD_TYPE mockcpp_testngpp
