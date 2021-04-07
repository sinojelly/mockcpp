# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.

# $args[0]  --- [optional] compiler index in table $global:SUPPORTED_COMPILER in tools\build_functions.ps1

# Set the install path, should be absolute path
$INSTALL_PATH="D:\Develop\test_tools\mockcpp-install"

$global:USER_CHOICE=$null
$global:SUPPORTED_COMPILER=$null

. "$PSScriptRoot\..\..\..\tools\build_functions.ps1"

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

Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S . -B $BUILD_DIR/testngpp-install -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH"
CompileProjectInstall $global:MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp-install
