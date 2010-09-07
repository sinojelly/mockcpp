
INCLUDE(FindPythonInterp)

IF(PYTHONINTERP_FOUND)
  SET(PYTHON ${PYTHON_EXECUTABLE})
ELSE(PYTHONINTERP_FOUND)
  MESSAGE(FATAL_ERROR "No Python interpreter found")
ENDIF(PYTHONINTERP_FOUND)

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
  TestMethodInfoReader.h
  TestMockObject.h
  TestMockObject2.h
  TestReturnObjectList.h
  TestStringConstraint.h
  TestStubContainter.h
  TestVirtualTable.h
  TestCheck.h
  TestBlockAllocator.h
)

LINK_DIRECTORIES(
	${PROJECT_HOME}/../../build/src/Debug
	${PROJECT_HOME}/../../build_testngpp/src/Debug
  ${PROJECT_HOME}/src
  ${CMAKE_BINARY_DIR}/3rdparty/testngpp/src)

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
ENDIF(MSVC)

FOREACH(CASE ${UT_CASES})
  GET_FILENAME_COMPONENT(CASE_NAME ${CASE} NAME_WE)
  SET(CASE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${CASE_NAME}.cpp)

  ADD_CUSTOM_TARGET(${CASE_NAME} DEPENDS ${CASE_SRC})

  SET(CASE_MODULE ${TESTCASE_PREFIX}-${CASE_NAME})

  ADD_LIBRARY(${CASE_MODULE} MODULE ${CASE_SRC})

  TARGET_LINK_LIBRARIES(${CASE_MODULE}
    testngpp
    mockcpp)

  ADD_CUSTOM_COMMAND(
    OUTPUT ${CASE_SRC}
    COMMAND ${PYTHON} ${TEST_GENERATOR} -o ${CASE_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/${CASE}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${CASE}
  )

  ADD_DEPENDENCIES(${CASE_MODULE} ${CASE_NAME})
ENDFOREACH()


