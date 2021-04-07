# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.

# $args[0]  --- [optional] compiler index in table $global:SUPPORTED_COMPILER in tools\build_functions.ps1
# $args[1]  --- [optional] if it is "test" then only run tests without compiling.

$global:USER_CHOICE=$null
$global:SUPPORTED_COMPILER=$null

. "$PSScriptRoot\..\..\..\tools\build_functions.ps1"

# If no input parameter
if (-not $args[0]) {
    # Detect the compiler
    cmake -B build ../../../tools
    ReadUserChoice
} else {
    $global:USER_CHOICE=$args[0] 
}

$global:MY_OS_NAME=$null
$global:MY_CXX_COMPILER_NAME=$null
$global:MY_CXX_COMPILER_MAJOR_VERSION=$null
$global:CMAKE_COMPILER_PARAM=$null
$global:MAKE_BUILD_TYPE=$null

InitEnviroment $global:SUPPORTED_COMPILER[$global:USER_CHOICE].name $global:SUPPORTED_COMPILER[$global:USER_CHOICE].major_ver $global:SUPPORTED_COMPILER[$global:USER_CHOICE].cmake_param

$BUILD_DIR="build_$global:MY_CXX_COMPILER_NAME"

$OS_COMPILER="$global:MY_OS_NAME\$global:MY_CXX_COMPILER_NAME\$global:MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER in Powershell : $OS_COMPILER"

if (-not ($args[1] -eq "test")) {
Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S . -B $BUILD_DIR/testngpp"
Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S tests/3rdparty/testngppst -B $BUILD_DIR/testngpp_testngppst"
Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S tests -B $BUILD_DIR/testngpp_tests"
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp_testngppst
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp_tests
}

RunTests $BUILD_DIR testngpp_tests $global:MAKE_BUILD_TYPE testngpp_testngppst st
