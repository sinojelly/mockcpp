# Build System Description
## Build environment preparation 

### Linux 
Install these tools：
```
sudo apt install git
sudo apt install gcc
sudo apt install g++
sudo apt install cmake
```
### Windows

Install Visual Studio or MinGW, Cygwin haven't been tested.

## Testing Tools Build Steps

### Background information

In order to reuse the prebuilt binary files, the new build system put the generated binary files into OS_NAME/COMPILER_NAME/COMPILER_MAJOR_VERSION directory, eg: for VS2019 the directory is Windows/MSVC/19.

To make sure cmake can find the right directory, the OS_NAME、COMPILER_NAME、COMPILER_MAJOR_VERSION must be the same as the output of running cmake on this CMakeLists.txt :
``` cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.19)
PROJECT(cmake-test)

MESSAGE("CMAKE_SYSTEM_NAME - OS_NAME:")
MESSAGE(${CMAKE_SYSTEM_NAME})

MESSAGE("CMAKE_CXX_COMPILER_ID - COMPILER_NAME:")
MESSAGE(${CMAKE_CXX_COMPILER_ID})

MESSAGE("CMAKE_CXX_COMPILER_VERSION - COMPILER_MAJOR_VERSION:")
MESSAGE(${CMAKE_CXX_COMPILER_VERSION})
```

You can use the output information in standard output like this :
```
OS_COMPILER in Powershell: Windows\GNU\8
```
and this :
```
TESTNGPP_OS_COMPILER in CMakeLists:
Windows/GNU/8
```
to check whether it is working properly.

### Linux
#### mockcpp
##### Build and run tests
If you use GNU 8.x, you can use these commands:
```
cd path/to/mockcpp
./build.sh GNU 8
```
##### Build and install
TODO: Script need to be updated.

#### testngpp
##### Build and run tests
If you use GNU 8.x, you can use these commands:
```
cd path/to/mockcpp/tests/3rdparty/testngpp
./build.sh GNU 8
```
##### Build and install
TODO: Script need to be updated.

### Windows
#### mockcpp
##### Build and run tests
If you use VS2019, you can use these commands:
```
cd path/to/mockcpp
.\build.ps1 2
```
The parameter 2 is the index of $SUPPORTED_COMPILER in build.ps1:
``` powershell
$SUPPORTED_COMPILER = @(
           @{ name="GNU"; major_ver="7"; cmake_param="-G `"MinGW Makefiles`""},  # 0 --- MinGW GNU 7.x
           @{ name="GNU"; major_ver="8"; cmake_param="-G `"MinGW Makefiles`""},  # 1 --- MinGW GNU 8.x
           @{ name="MSVC"; major_ver="19"; cmake_param="-G `"Visual Studio 16 2019`"" }  # 2 --- Visual Studio 2019
          )
```
You can update this $SUPPORTED_COMPILER table to support more compilers, you can also submit a pull request, thanks.

##### Build and install
TODO: Script need to be updated.

#### testngpp
##### Build and run tests
If you use VS2019, you can use these commands:
```
cd path/to/mockcpp
.\build.ps1 2
```
The parameter 2 is the index of $SUPPORTED_COMPILER in build.ps1.

##### Build and install
TODO: Script need to be updated.


## User project build suggestion

In order to develop faster, we use the prebuilt binary files of the testing tools, avoid compiling the testing tools each time while we compiling our product project.

But because of ABI compatible issues of different compiler versions, maybe we encounter some runtime error. So I suggest you to replace the prebuilt binary files with yours that was built in the same enviroment as your product project. Be sure to follow the OS_NAME/COMPILER_NAME/COMPILER_MAJOR_VERSION directory structure convention.

### 1. Refer the sample project
https://gitee.com/sinojelly/testngpp-mockcpp-sample

### 2. Replace the prebuilt binary files with yours.
Be sure to follow the OS_NAME/COMPILER_NAME/COMPILER_MAJOR_VERSION directory structure convention.

### 3. Use the build.sh or build.ps1 to build.
The usage is the same as build mockcpp or testngpp.
