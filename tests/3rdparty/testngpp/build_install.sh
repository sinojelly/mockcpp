#!/bin/bash
# build and install

# $1  --- [optional] compiler name  (default is GNU)
# $2  --- [optional] compiler major version  (The first part of cxx compiler version)

# fast fail
set -e

# Set the install path, should be absolute path
INSTALL_PATH=~/test_tools/mockcpp_install

. "../../../tools/build_functions.sh"

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

cmake  -S . -B $BUILD_DIR/testngpp-install -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH

CompileProjectInstall $MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp-install
