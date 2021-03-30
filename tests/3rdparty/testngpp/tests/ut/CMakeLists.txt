
find_package (Python3 COMPONENTS Interpreter)

IF(Python3_FOUND)
    SET(PYTHON ${Python3_EXECUTABLE})
ELSE()
    MESSAGE(FATAL_ERROR "No Python interpreter found")
ENDIF(Python3_FOUND)

SET(BOOST_ROOT       ${CMAKE_SOURCE_DIR}/../../../../3rdparty)

FIND_FILE(BOOST_HEADER
            typeof.hpp 
            PATHS ${BOOST_ROOT}/boost/typeof 
            NO_DEFAULT_PATH 
            NO_CMAKE_ENVIRONMENT_PATH 
            NO_CMAKE_PATH 
            NO_SYSTEM_ENVIRONMENT_PATH 
            NO_CMAKE_SYSTEM_PATH)
IF(NOT EXISTS ${BOOST_HEADER})
ADD_DEFINITIONS(-DNO_BOOST=1)
ENDIF()

ADD_DEFINITIONS(
    -DPACKAGE_NAME=${PACKAGE_NAME}
    -DPACKAGE_STRING=${PACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
)

IF(NOT MSVC)
ADD_DEFINITIONS(
  -std=c++11
)
ENDIF(NOT MSVC)

SET(UT_CASES
  TestAssertionFailure.h    
  TestPosixFNMatcher.h
  TestStringToOptions.h
  TestTagsParser.h
  TestTestCase.h
  TestTestFixtureDesc.h
  TestTestSuiteDesc.h
  TestXMLBuilder.h
  TestDataDriven.h
  TestMemChecker.h
  TestAsserter.h
)

IF(UNIX)
  SET(UT_CASES
  ${UT_CASES}
  TestModuleTestSuiteLoader.h
  TestPipeReadableChannel.h
  TestPipeWrittableChannel.h
  )
ENDIF(UNIX)

SET(UT_CASES_WITH_MOCK
  TestTestCaseHierarchy.h
  TestXMLTestListener.h
  TestTestFilterFactory.h
  TestOrCompositeTestFilter.h
  TestSimpleTestSuiteResultReporter.h
  TestGeneralTestFilter.h
)

IF(UNIX)
  SET(UT_CASES_WITH_MOCK
  ${UT_CASES_WITH_MOCK}
  TestSandbox.h
  TestSandboxProcessor.h
  TestTestCaseSandboxResultReporter.h
  TestTestFixtureSandboxRunner.h
  TestTestSuiteContext.h  
  )
ENDIF(UNIX)

SET(UT_CASES ${UT_CASES} ${UT_CASES_WITH_MOCK})

LINK_DIRECTORIES(
  ${CMAKE_BINARY_DIR}/../testngpp_testngppst/src
  ${CMAKE_BINARY_DIR}/../testngpp/src
  ${CMAKE_BINARY_DIR}/../testngpp/src/utils
  ${CMAKE_BINARY_DIR}/../testngpp/src/runner
  ${CMAKE_BINARY_DIR}/../testngpp/src/listeners
  ${CMAKE_BINARY_DIR}/../testngpp_testngppst/src/Debug
  ${CMAKE_BINARY_DIR}/../testngpp/src/Debug
  ${CMAKE_BINARY_DIR}/../testngpp/src/utils/Debug
  ${CMAKE_BINARY_DIR}/../testngpp/src/runner/Debug
  ${CMAKE_BINARY_DIR}/../testngpp/src/listeners/Debug)

INCLUDE_DIRECTORIES(BEFORE 
  .
  ${PROJECT_HOME}/include
  ${PROJECT_HOME}/3rdparty
  ${PROJECT_HOME}/src
  ${CMAKE_SOURCE_DIR}/3rdparty/testngppst/include
  ${CMAKE_SOURCE_DIR}/3rdparty/mockcpp/include
  ${BOOST_ROOT}
  )

SET(TEST_GENERATOR ${CMAKE_SOURCE_DIR}/3rdparty/testngppst/scripts/testngppstgen.py)
SET(TESTCASE_PREFIX testngpp-ut)

FOREACH(CASE ${UT_CASES})
  GET_FILENAME_COMPONENT(CASE_NAME ${CASE} NAME_WE)
  SET(CASE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${CASE_NAME}.cpp)

  ADD_CUSTOM_TARGET(${CASE_NAME} DEPENDS ${CASE_SRC})

  SET(CASE_MODULE ${TESTCASE_PREFIX}-${CASE_NAME})

  IF(MSVC)
  ADD_DEFINITIONS(-DMSVC_VMG_ENABLED)
  ENDIF(MSVC)

  ADD_LIBRARY(${CASE_MODULE} MODULE ${CASE_SRC})

  TARGET_LINK_LIBRARIES(${CASE_MODULE}
    testngppst
    testngpp-utils
    testngpp-static
    testngpp-runner-lib
    testngppxmllistener-fortest
    mockcpp)

  ADD_CUSTOM_COMMAND(
    OUTPUT ${CASE_SRC}
    COMMAND ${PYTHON} ${TEST_GENERATOR} -o ${CASE_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/${CASE}	
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${CASE}
  )

  ADD_DEPENDENCIES(${CASE_MODULE} ${CASE_NAME})
ENDFOREACH()

IF(UNIX)
ADD_DEFINITIONS(-g -ggdb)
ENDIF(UNIX)
