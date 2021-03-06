function(SetCompilerMajorVersion COMPILER_VERSION)
  string(REPLACE "." ";" COMPONENT_LIST ${COMPILER_VERSION})
  list(GET COMPONENT_LIST 0 MAJOR_VERSION)
  set(COMPILER_MAJOR_VERSION ${MAJOR_VERSION} PARENT_SCOPE)
endfunction()

SetCompilerMajorVersion(${CMAKE_CXX_COMPILER_VERSION})

SET(TESTNGPP_OS_NAME ${CMAKE_SYSTEM_NAME})
SET(TESTNGPP_CXX_COMPILER_NAME ${CMAKE_CXX_COMPILER_ID})
SET(TESTNGPP_CXX_COMPILER_MAJOR_VERSION ${COMPILER_MAJOR_VERSION})
SET(TESTNGPP_OS_COMPILER ${TESTNGPP_OS_NAME}/${TESTNGPP_CXX_COMPILER_NAME}/${TESTNGPP_CXX_COMPILER_MAJOR_VERSION})