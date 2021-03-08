
INCLUDE(FindPythonInterp)

IF(PYTHONINTERP_FOUND)
  SET(PYTHON ${PYTHON_EXECUTABLE})
ELSE(PYTHONINTERP_FOUND)
  MESSAGE(FATAL_ERROR "No Python interpreter found")
ENDIF(PYTHONINTERP_FOUND)

IF(MSVC)
  SET(RM del)
ELSE(MSVC)
  SET(RM rm -rf)
ENDIF(MSVC)

SET(THIS_DIR ${CMAKE_SOURCE_DIR}/scripts)

ADD_CUSTOM_TARGET(compile-testngppstgen ALL
   COMMAND ${PYTHON} ${THIS_DIR}/pycompile.py ${THIS_DIR}) 
   
ADD_CUSTOM_TARGET(cleanup-testngppstgen
   COMMAND ${RM} ${THIS_DIR}/*.pyc ${THIS_DIR}/testngppstgen/*.pyc)

SET(PYC_FILES 
  ${THIS_DIR}/testngppstgen.pyc
  ${THIS_DIR}/testngppstgen/AnnotationParser.pyc
  ${THIS_DIR}/testngppstgen/ElemParser.pyc 
  ${THIS_DIR}/testngppstgen/Fixture.pyc
  ${THIS_DIR}/testngppstgen/FixtureParser.pyc
  ${THIS_DIR}/testngppstgen/Generator.pyc
  ${THIS_DIR}/testngppstgen/LogicalLine.pyc
  ${THIS_DIR}/testngppstgen/Message.pyc
  ${THIS_DIR}/testngppstgen/Name.pyc
  ${THIS_DIR}/testngppstgen/Phase0.pyc
  ${THIS_DIR}/testngppstgen/Phase1.pyc
  ${THIS_DIR}/testngppstgen/Phase1Result.pyc
  ${THIS_DIR}/testngppstgen/Phase2.pyc
  ${THIS_DIR}/testngppstgen/Phase3.pyc
  ${THIS_DIR}/testngppstgen/Phase4.pyc
  ${THIS_DIR}/testngppstgen/PreprocessScope.pyc
  ${THIS_DIR}/testngppstgen/PreprocessScopeParser.pyc
  ${THIS_DIR}/testngppstgen/Process.pyc
  ${THIS_DIR}/testngppstgen/TagsParser.pyc
  ${THIS_DIR}/testngppstgen/TestCase.pyc
  ${THIS_DIR}/testngppstgen/TestCaseParser.pyc
  ${THIS_DIR}/testngppstgen/TestScope.pyc
  ${THIS_DIR}/testngppstgen/Output.pyc
  ${THIS_DIR}/testngppstgen/__init__.pyc)

FILE(REMOVE ${PYC_FILES})

INSTALL(DIRECTORY . DESTINATION testngppst/generator
       FILES_MATCHING PATTERN "*.pyc"
       PATTERN "CMakeFiles" EXCLUDE
       PATTERN ".svn" EXCLUDE
       PATTERN ".py" EXCLUDE)
