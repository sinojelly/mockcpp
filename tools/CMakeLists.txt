CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.19)
PROJECT(EnviromentTest)

INCLUDE(testngpp.cmake)

set(CMAKE_INSTALL_MESSAGE NEVER)

find_package (Python3 COMPONENTS Interpreter)
IF(NOT Python3_FOUND)
    MESSAGE(FATAL_ERROR "Please install python3 first.")
ENDIF(NOT Python3_FOUND)

MESSAGE("")
MESSAGE("The compiler that CMake automatically detects is:")
MESSAGE("")
MESSAGE("OS: " ${TESTNGPP_OS_NAME})
MESSAGE("Compiler: " ${TESTNGPP_CXX_COMPILER_NAME})
MESSAGE("Compiler version: " ${CMAKE_CXX_COMPILER_VERSION})
MESSAGE("Compiler major version: " ${TESTNGPP_CXX_COMPILER_MAJOR_VERSION})
MESSAGE("")
MESSAGE("You can select other installed compilers.")
MESSAGE("")
