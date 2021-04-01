# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.

# $args[0]  --- compiler index in table $SUPPORTED_COMPILER
# $args[2]  --- install dir, it's an absolute path

. "$PSScriptRoot\..\..\..\tools\build_functions.ps1"

# Use the following content to make a CMakeLists.txt to get compiler name and major_ver, run : cmake -S . -B build
# CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.19)
# PROJECT(cmake-test)
# MESSAGE("CMAKE_CXX_COMPILER_ID - compiler name:")
# MESSAGE(${CMAKE_CXX_COMPILER_ID})
# MESSAGE("CMAKE_CXX_COMPILER_VERSION - compiler major version:")
# MESSAGE(${CMAKE_CXX_COMPILER_VERSION})
#
# cmake_param also can be: "-G `"Visual Studio 16 2019`" -A Win32"  etc.
$SUPPORTED_COMPILER = @(
           @{ name="GNU"; major_ver="7"; cmake_param="-G `"MinGW Makefiles`""},  # 0 --- MinGW GNU 7.x
           @{ name="GNU"; major_ver="8"; cmake_param="-G `"MinGW Makefiles`""},  # 1 --- MinGW GNU 8.x
           @{ name="MSVC"; major_ver="19"; cmake_param="-G `"Visual Studio 16 2019`"" }  # 2 --- Visual Studio 2019
          )

# If no input parameter
if (-not $args[0]) {
    $DEFAULT_COMPILER_INDEX=2   # default choose vs2019
} else {
    $DEFAULT_COMPILER_INDEX=$args[0] 
}

if (-not $args[1]) {
    $DEFAULT_INSTALL_PATH="D:\Develop\test-tools\testngpp-install"   # should be absolute path
} else {
    $DEFAULT_INSTALL_PATH=$args[1] 
}

if (!(test-path $DEFAULT_INSTALL_PATH)) { mkdir $DEFAULT_INSTALL_PATH }

$global:MY_OS_NAME=$null
$global:MY_CXX_COMPILER_NAME=$null
$global:MY_CXX_COMPILER_MAJOR_VERSION=$null
$global:CMAKE_COMPILER_PARAM=$null
$global:MAKE_BUILD_TYPE=$null

InitEnviroment $SUPPORTED_COMPILER[$DEFAULT_COMPILER_INDEX].name $SUPPORTED_COMPILER[$DEFAULT_COMPILER_INDEX].major_ver $SUPPORTED_COMPILER[$DEFAULT_COMPILER_INDEX].cmake_param

$BUILD_DIR="build_$global:MY_CXX_COMPILER_NAME"

$OS_COMPILER="$global:MY_OS_NAME\$global:MY_CXX_COMPILER_NAME\$global:MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER in Powershell : $OS_COMPILER"

Invoke-Expression "cmake $global:CMAKE_COMPILER_PARAM -S . -B $BUILD_DIR/testngpp-install -DCMAKE_INSTALL_PREFIX=$DEFAULT_INSTALL_PATH"
CompileProjectInstall $global:MY_CXX_COMPILER_NAME $BUILD_DIR/testngpp-install
