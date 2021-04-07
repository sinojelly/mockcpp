# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.

# $args[0]  --- [optional] compiler index in table $global:SUPPORTED_COMPILER in tools\build_functions.ps1

# Set the install path, should be absolute path
$INSTALL_PATH="D:\Develop\test_tools\mockcpp-install"

# Set the xxunit test framework name, default testngpp
$XUNIT_NAME="testngpp"
#$XUNIT_NAME="gtest"
#$XUNIT_NAME="catch2"

# testngpp: not need $XUNIT_HOME
# gtest: there is a $XUNIT_HOME/include/gtest/gtest.h
# catch2: there is a $XUNIT_HOME/catch2/catch_test_macros.hpp
#$XUNIT_HOME="D:/Develop/work/googletest/googletest"
#$XUNIT_HOME="D:/Develop/work/Catch2/src"

$global:USER_CHOICE=$null
$global:SUPPORTED_COMPILER=$null

. "$PSScriptRoot\tools\build_functions.ps1"

# If no input parameter
if (-not $args[0]) {
    # Detect the compiler
    cmake -B build tools
    ReadUserChoice
} else {
    $global:USER_CHOICE=$args[0] 
}

if (!(test-path $INSTALL_PATH)) { mkdir $INSTALL_PATH }

$global:MY_OS_NAME=$null
$global:MY_CXX_COMPILER_NAME=$null
$global:MY_CXX_COMPILER_MAJOR_VERSION=$null
$global:CMAKE_COMPILER_PARAM=$null
$global:MAKE_BUILD_TYPE=$null

InitEnviroment $global:SUPPORTED_COMPILER[$global:USER_CHOICE].name $global:SUPPORTED_COMPILER[$global:USER_CHOICE].major_ver $global:SUPPORTED_COMPILER[$global:USER_CHOICE].cmake_param

$BUILD_DIR="build_$global:MY_CXX_COMPILER_NAME"

$OS_COMPILER="$global:MY_OS_NAME\$global:MY_CXX_COMPILER_NAME\$global:MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER in Powershell : $OS_COMPILER"

$XUNIT_DEFINE=""
if ($XUNIT_NAME -ne "testngpp") {
    $XUNIT_DEFINE="-DMOCKCPP_XUNIT=$XUNIT_NAME -DMOCKCPP_XUNIT_HOME=$XUNIT_HOME"
}

Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S . -B $BUILD_DIR/mockcpp-install4$XUNIT_NAME -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH $XUNIT_DEFINE"
CompileProjectInstall $global:MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp-install4$XUNIT_NAME
