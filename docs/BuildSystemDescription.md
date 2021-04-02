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
If you use GNU 8.x, you can modify the INSTALL_PATH XUNIT_NAME XUNIT_HOME in the script and then use these commands:
```
cd path/to/mockcpp
./build_install.sh GNU 8
```

#### testngpp
##### Build and run tests
If you use GNU 8.x, you can use these commands:
```
cd path/to/mockcpp/tests/3rdparty/testngpp
./build.sh GNU 8
```
##### Build and install
If you use GNU 8.x, you can modify the INSTALL_PATH in the script and then use these commands:
```
cd path/to/mockcpp/tests/3rdparty/testngpp
./build_install.sh GNU 8
```

### Windows
#### mockcpp
##### Build and run tests
If you use VS2019, you can use these commands:
```
cd path/to/mockcpp
.\build.ps1 2
```
The parameter 2 is the index of $global:SUPPORTED_COMPILER in tools\build_functions.ps1:
``` powershell
# cmake_param also can be: "-G `"Visual Studio 16 2019`" -A Win32"  etc.
$global:SUPPORTED_COMPILER = @(
           @{ name="GNU"; major_ver="7"; cmake_param="-G `"MinGW Makefiles`""},  # 0 --- MinGW GNU 7.x
           @{ name="GNU"; major_ver="8"; cmake_param="-G `"MinGW Makefiles`""},  # 1 --- MinGW GNU 8.x
           @{ name="MSVC"; major_ver="19"; cmake_param="-G `"Visual Studio 16 2019`"" }  # 2 --- Visual Studio 2019
          )
```
You can update this $global:SUPPORTED_COMPILER table to support more compilers, you can also submit a pull request.

In order to find the compiler name and major version, you can use the following content to make a CMakeLists.txt and run : cmake -S . -B build
```
CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.19)
PROJECT(cmake-test)
MESSAGE("CMAKE_CXX_COMPILER_ID - compiler name:")
MESSAGE(${CMAKE_CXX_COMPILER_ID})
MESSAGE("CMAKE_CXX_COMPILER_VERSION - compiler major version:")
MESSAGE(${CMAKE_CXX_COMPILER_VERSION})
```

##### Build and install
If you use VS2019, you can modify the INSTALL_PATH XUNIT_NAME XUNIT_HOME in the script and then use these commands:
```
cd path/to/mockcpp
.\build_install.ps1 2
```
The parameter 2 is the index of $global:SUPPORTED_COMPILER in tools\build_functions.ps1, It's the same as **Build and run tests**.

#### testngpp
##### Build and run tests
If you use VS2019, you can use these commands:
```
cd path/to/mockcpp/tests/3rdparty/testngpp
.\build.ps1 2
```
The parameter 2 is the index of $global:SUPPORTED_COMPILER in tools\build_functions.ps1.

##### Build and install
If you use VS2019, you can modify the INSTALL_PATH in the script use these commands:
```
cd path/to/mockcpp/tests/3rdparty/testngpp
.\build_install.ps1 2
```
The parameter 2 is the index of $global:SUPPORTED_COMPILER in tools\build_functions.ps1.


## User project build suggestion

### Method 1: Use mockcpp testngpp prebuilt binaries

In order to develop faster, we use the prebuilt binary files of the testing tools, avoid compiling the testing tools each time while we compiling our product project.

But because of ABI compatible issues of different compiler versions, maybe we encounter some runtime error. So I suggest you to replace the prebuilt binary files with yours that was built in the same enviroment as your product project. Be sure to follow the OS_NAME/COMPILER_NAME/COMPILER_MAJOR_VERSION directory structure convention.

#### 1) Refer the sample project
https://gitee.com/sinojelly/testngpp-mockcpp-sample

#### 2) Replace the prebuilt binary files with yours.
You can build_install mockcpp testngpp and update the files in testngpp-mockcpp-sample/tests/testngpp.
Be sure to follow the OS_NAME/COMPILER_NAME/COMPILER_MAJOR_VERSION directory structure convention.

#### 3) Use the build.sh or build.ps1 to build.
The usage is the same as build mockcpp or testngpp.

### Method 2: Use mockcpp testngpp source code

You can also use mockcpp testngpp source code in your project, but it may take some time to compile. The sample project use mockcpp testngpp source code is here:
https://gitee.com/sinojelly/testngpp-mockcpp-sample-src