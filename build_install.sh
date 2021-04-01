#!/bin/bash
# build and install

# $1  --- compiler name  (GNU)
# $2  --- [optional] compiler major version  (The first part of cxx compiler version)

# fast fail
set -e

# Set the install path, should be absolute path
INSTALL_PATH=~/test_tools/mockcpp_install

# Set the xxunit test framework name
XUNIT_NAME=testngpp
#XUNIT_NAME=gtest
#XUNIT_NAME=catch2

# gtest: there is a $XUNIT_HOME/include/gtest/gtest.h
# catch2: there is a $XUNIT_HOME/include/catch2/catch_test_macros.hpp
#XUNIT_HOME=/usr/local

. "tools/build_functions.sh"

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

if [ "$XUNIT_NAME" == "testngpp" ];then
cmake  -S . -B $BUILD_DIR/mockcpp-install4$XUNIT_NAME -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH
else
cmake  -S . -B $BUILD_DIR/mockcpp-install4$XUNIT_NAME -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DMOCKCPP_XUNIT=$XUNIT_NAME -DMOCKCPP_XUNIT_HOME=$XUNIT_HOME
fi

CompileProjectInstall $MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp-install4$XUNIT_NAME

