# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.

# $args[0]  --- compiler name  (GNU, MSVC)
# $args[1]  --- [optional] compiler major version  (The first part of cxx compiler version)

. "$PSScriptRoot\..\..\..\tools\build_functions.ps1"

$global:MY_OS_NAME=$null
$global:MY_CXX_COMPILER_NAME=$null
$global:MY_CXX_COMPILER_MAJOR_VERSION=$null
$global:CMAKE_COMPILER_PARAM=$null
$global:MAKE_BUILD_TYPE=$null

$AUTO_COMPILER="GNU"    #  $args[0]
$AUTO_CXX_VER="8"       #  $args[1]
#InitEnviroment $AUTO_COMPILER $AUTO_CXX_VER
InitEnviroment $args[0] $args[1]

$BUILD_DIR="build_$global:MY_CXX_COMPILER_NAME"

$OS_COMPILER="$global:MY_OS_NAME\$global:MY_CXX_COMPILER_NAME\$global:MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER in Powershell : $OS_COMPILER"

Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S . -B $BUILD_DIR/testngpp"
Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S tests/3rdparty/testngppst -B $BUILD_DIR/testngpp_testngppst"
Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S tests -B $BUILD_DIR/testngpp_tests"
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp_testngppst
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp_tests

RunTests $BUILD_DIR testngpp_tests $global:MAKE_BUILD_TYPE testngpp_testngppst st
