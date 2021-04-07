CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.19)
PROJECT(EnviromentTest)

INCLUDE(testngpp.cmake)

set(CMAKE_INSTALL_MESSAGE NEVER)

find_package (Python3 COMPONENTS Interpreter)
IF(NOT Python3_FOUND)
    MESSAGE(FATAL_ERROR "Please install python3 first.")
ENDIF(NOT Python3_FOUND)

SetCompilerMajorVersion(${CMAKE_CXX_COMPILER_VERSION})

MESSAGE("")
MESSAGE("The compiler that CMake automatically detects is:")
MESSAGE("")
MESSAGE("Compiler: " ${CMAKE_CXX_COMPILER_ID})
MESSAGE("Compiler version: " ${CMAKE_CXX_COMPILER_VERSION})
MESSAGE("Compiler major version: " ${COMPILER_MAJOR_VERSION})
MESSAGE("")
MESSAGE("You can select other installed compilers.")
MESSAGE("")
