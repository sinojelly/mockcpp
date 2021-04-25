
find_package (Python3 COMPONENTS Interpreter)

IF(Python3_FOUND)
    SET(PYTHON ${Python3_EXECUTABLE})
ELSE()
    MESSAGE(FATAL_ERROR "No Python interpreter found")
ENDIF(Python3_FOUND)

ADD_DEFINITIONS(
    -DPACKAGE_NAME=${PACKAGE_NAME}
    -DPACKAGE_STRING=${PACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
)

SET(UT_CASES
  TestAny.h
  TestChainableMockMethod.h
  TestChainableMockMethodContainer.h
  TestChainableMockMethodNameKey.h
  TestChainableObject.h
  TestConstraintSet.h
  TestDelegatedMethod.h
  TestDestructorChecker.h
  TestFormatter.h
  TestHolder.h
  TestIncrementStub.h
  TestInterfaceInfo.h
  TestInvocation.h
  TestInvocationMocker.h
  TestIsEqual.h
  TestIsStringContains.h
  TestIsStringEndWith.h
  TestIsStringStartWith.h
  TestMockObject.h
  TestMockObject2.h
  TestReturnObjectList.h
  TestStringConstraint.h
  TestStubContainter.h
  TestCheck.h
  TestApiHook.h
  TestStaticMethodMocker.h
  #TestNonvirtualMethodMocker.h
  TestMockcppSample.h
  TestApiHookBase.h
  TestSmartPointerChecker.h
  MockMethodSamples.h
)

IF(UNIX)
  SET(UT_CASES
  ${UT_CASES}
  TestMethodInfoReader.h
  TestVirtualTable.h
  )
ENDIF(UNIX)

IF(MSVC)
  SET(UT_CASES
  ${UT_CASES}
  TestApiHookStdcall.h
  )
ENDIF(MSVC)

IF(CMAKE_CL_64)
    ADD_DEFINITIONS(-DWIN64)
ENDIF(CMAKE_CL_64)

IF(MSVC)
LINK_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}/../../mockcpp/src/Debug
	${CMAKE_CURRENT_BINARY_DIR}/../../mockcpp_testngpp/src/Debug)
ELSE(MSVC)
LINK_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}/../../mockcpp/src
  ${CMAKE_CURRENT_BINARY_DIR}/../../mockcpp_testngpp/src)
ENDIF(MSVC)

INCLUDE_DIRECTORIES(BEFORE 
  .
  ${PROJECT_HOME}/include
  ${PROJECT_HOME}/3rdparty
  ${CMAKE_SOURCE_DIR}/3rdparty/testngpp/include
  )

SET(TEST_GENERATOR ${CMAKE_SOURCE_DIR}/3rdparty/testngpp/scripts/testngppgen.py)
SET(TESTCASE_PREFIX mockcpp-ut)

IF(MSVC)
    ADD_DEFINITIONS(-DMSVC_VMG_ENABLED)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /vmg")
    ADD_DEFINITIONS(
      /source-charset:utf-8 /execution-charset:utf-8 )
ELSE(MSVC)
    ADD_DEFINITIONS(-std=c++14)
ENDIF(MSVC)

IF(UNIX OR MINGW)
ADD_DEFINITIONS(
    -g -ggdb
)
ENDIF(UNIX OR MINGW)

IF(UNIX AND NOT CYGWIN)
ADD_DEFINITIONS(
    -fPIC
)
ENDIF(UNIX AND NOT CYGWIN)

FIND_FILE(BOOST_HEADER
            typeof.hpp 
            PATHS ${PROJECT_HOME}/3rdparty/boost/typeof 
            NO_DEFAULT_PATH 
            NO_CMAKE_ENVIRONMENT_PATH 
            NO_CMAKE_PATH 
            NO_SYSTEM_ENVIRONMENT_PATH 
            NO_CMAKE_SYSTEM_PATH)
IF(NOT EXISTS ${BOOST_HEADER})
ADD_DEFINITIONS(-DNO_BOOST=1)
ENDIF()

FOREACH(CASE ${UT_CASES})
  GET_FILENAME_COMPONENT(CASE_NAME ${CASE} NAME_WE)
  SET(CASE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${CASE_NAME}.cpp)

  ADD_CUSTOM_TARGET(${CASE_NAME} DEPENDS ${CASE_SRC})

  SET(CASE_MODULE ${TESTCASE_PREFIX}-${CASE_NAME})

  ADD_LIBRARY(${CASE_MODULE} MODULE ${CASE_SRC})

  TARGET_LINK_LIBRARIES(${CASE_MODULE}
    testngpp-static
    mockcpp)

  ADD_CUSTOM_COMMAND(
    OUTPUT ${CASE_SRC}
    COMMAND ${PYTHON} ${TEST_GENERATOR} -e utf-8 -o ${CASE_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/${CASE}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${CASE}
  )

  ADD_DEPENDENCIES(${CASE_MODULE} ${CASE_NAME})
ENDFOREACH()
