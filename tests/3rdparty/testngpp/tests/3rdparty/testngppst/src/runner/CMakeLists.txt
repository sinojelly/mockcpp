
IF(MSVC)
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
ENDIF(MSVC)

IF(NOT DEFINED TESTNGPPST_DISABLE_RC)
  SET(TESTNGPPST_DISABLE_RC FALSE)
ENDIF(NOT DEFINED TESTNGPPST_DISABLE_RC)

IF(NOT DEFINED TESTNGPPST_DISABLE_SANDBOX)
  SET(TESTNGPPST_DISABLE_SANDBOX FALSE)
ENDIF(NOT DEFINED TESTNGPPST_DISABLE_SANDBOX)

IF(TESTNGPPST_DISABLE_SANDBOX)
  ADD_DEFINITIONS(-DTESTNGPPST_DISABLE_SANDBOX=1)
ELSE(TESTNGPPST_DISABLE_SANDBOX)
  ADD_DEFINITIONS(-DTESTNGPPST_DISABLE_SANDBOX=0)
ENDIF(TESTNGPPST_DISABLE_SANDBOX)

IF(TESTNGPPST_DISABLE_RC)
  ADD_DEFINITIONS(-DTESTNGPPST_DISABLE_RC=1)
ELSE(TESTNGPPST_DISABLE_RC)
  ADD_DEFINITIONS(-DTESTNGPPST_DISABLE_RC=0)
ENDIF(TESTNGPPST_DISABLE_RC)

ADD_DEFINITIONS(
    -DPACKAGE_NAME=${PACKAGE_NAME}
    -DPACKAGE_STRING=${PACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
)

SET(TESTNGPPST_LIBRARY testngppst testngppst-utils)

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/include)
ADD_DEFINITIONS(-D__STDC_FORMAT_MACROS)

IF (MSVC)
	INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/../../../3rdparty/msinttypes)
ENDIF()

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/src ${CMAKE_BINARY_DIR}/src/utils)

SET(RC_SRCS ResourceCheckPoint.cpp)

SET(SANDBOX_SRCS
  sandbox/TestCaseSandboxResultReporter.cpp 
  sandbox/TestCaseSandboxResultDecoder.cpp 
  sandbox/Sandbox.cpp 
  sandbox/SandboxProcessor.cpp 
  sandbox/TestCaseSandboxHandler.cpp 
  sandbox/TestCaseSandbox.cpp 
  sandbox/TestHierarchySandboxRunner.cpp 

  utils/PipeReadableChannel.cpp 
  utils/PipeWrittableChannel.cpp  
)

SET(WIN32_SANDBOX_SRCS
   sandbox/TestCaseSandboxResultReporter.cpp 
   sandbox/TestCaseSandboxResultDecoder.cpp  
   win32/Win32PipeWrittableChannel.cpp
   win32/Win32PipeReadableChannel.cpp
   win32/GetLastError.cpp
   win32/Win32TestHierarchySandboxRunner.cpp
   win32/Win32Sandbox.cpp
   win32/Win32TestCaseSandbox.cpp
)

SET(TESTNGRUNNER_LIB_SRCS
  runners/TestSuiteRunner.cpp 
  runners/SimpleTestCaseRunner.cpp 
  runners/TestFixtureRunner.cpp 
  runners/TestFixtureRunnerFactory.cpp 
  runners/SimpleTestHierarchyRunner.cpp 
  runners/TestCaseHierarchy.cpp
  runners/TestHierarchyHandler.cpp
  runners/TestSuiteContext.cpp
  runners/TestFixtureContext.cpp
  runners/TestRunnerContext.cpp
  runners/TestCaseRunnerFactory.cpp

  loaders/ModuleTestSuiteLoader.cpp 
  loaders/ModuleTestSuiteLoaderFactory.cpp 
  loaders/ModuleTestListenerLoader.cpp 
  loaders/ModuleTestListenerLoaderFactory.cpp 

  reports/SimpleTestResultDispatcher.cpp 
  reports/SimpleTestResultReporter.cpp 
  reports/SimpleTestCaseResultReporter.cpp 
  reports/SmartTestCaseResultCollector.cpp 
  reports/SimpleTestSuiteResultReporter.cpp
  reports/SimpleTestResultManager.cpp

  filters/WildcardTestFilter.cpp 
  filters/OrCompositeTestFilter.cpp 
  filters/GeneralTestFilter.cpp 
  filters/TestFilterFactory.cpp 
  filters/PosixFNMatcher.cpp 

  tags/AndCompositeTaggableFilter.cpp 
  tags/OrCompositeTaggableFilter.cpp 
  tags/NotCompositeTaggableFilter.cpp 
  tags/GeneralTagsFilter.cpp 
  tags/EmptyTagsFilter.cpp 
  tags/MatchAllTagsFilter.cpp 
  tags/TagsFilters.cpp 
  tags/TagsParser.cpp 
  tags/FixtureTagsFilter.cpp

  TestRunner.cpp
)

IF(NOT TESTNGPPST_DISABLE_RC)
   SET(TESTNGRUNNER_LIB_SRCS ${TESTNGRUNNER_LIB_SRCS} ${RC_SRCS})
ENDIF(NOT TESTNGPPST_DISABLE_RC)

IF(NOT TESTNGPPST_DISABLE_SANDBOX)
   IF(MSVC)
      SET(TESTNGRUNNER_LIB_SRCS
         ${TESTNGRUNNER_LIB_SRCS}
         ${WIN32_SANDBOX_SRCS}
      )
   ELSE(MSVC)
      SET(TESTNGRUNNER_LIB_SRCS
         ${TESTNGRUNNER_LIB_SRCS}
         ${SANDBOX_SRCS}
      )
   ENDIF(MSVC)
ENDIF(NOT TESTNGPPST_DISABLE_SANDBOX)

IF(MSVC)
  SET(TESTNGRUNNER_LIB_SRCS
     ${TESTNGRUNNER_LIB_SRCS}
     filters/Win32Fnmatch.c
  )
ENDIF(MSVC)

IF(TESTNGPPST_USE_DLOPEN)
  SET(TESTNGRUNNER_LIB_SRCS ${TESTNGRUNNER_LIB_SRCS}
      loaders/DLModuleLoader.cpp 
      loaders/DLModuleLoaderFactory.cpp
  )
ELSEIF(TESTNGPPST_USE_LTDL)
  SET(TESTNGRUNNER_LIB_SRCS ${TESTNGRUNNER_LIB_SRCS}
      loaders/LTModuleLoader.cpp 
      loaders/LTModuleLoaderFactory.cpp
  )
ELSEIF(TESTNGPPST_USE_LOADLIBRARY)
  SET(TESTNGRUNNER_LIB_SRCS ${TESTNGRUNNER_LIB_SRCS}
      loaders/Win32DllModuleLoader.cpp 
      loaders/Win32DllModuleLoaderFactory.cpp
  )
ELSE(TESTNGPPST_USE_DLOPEN)
  MESSAGE(FATAL_ERROR "No module loader found")
ENDIF(TESTNGPPST_USE_DLOPEN)

IF(UNIX)
ADD_DEFINITIONS(
    -g -ggdb
)
ENDIF(UNIX)

ADD_LIBRARY(testngppst-runner-lib STATIC ${TESTNGRUNNER_LIB_SRCS})

TARGET_LINK_LIBRARIES(testngppst-runner-lib ${TESTNGPPST_LIBRARY})

ADD_EXECUTABLE(testngppst-runner TestRunnerMain.cpp) 

IF(MSVC)
   ADD_EXECUTABLE(testngppst-win32-testcase-runner win32/TestCaseSandboxRunnerMain.cpp)
   TARGET_LINK_LIBRARIES(testngppst-win32-testcase-runner ${TESTNGPPST_LIBRARY} testngppst-runner-lib)

   INSTALL(TARGETS testngppst-win32-testcase-runner
      RUNTIME DESTINATION bin)
ENDIF(MSVC)

# -Wl,--export-dynamic
ADD_DEPENDENCIES(testngppst-runner testngppst-runner-lib)
TARGET_LINK_LIBRARIES(testngppst-runner ${TESTNGPPST_LIBRARY} testngppst-runner-lib)

IF(TESTNGPPST_USE_DLOPEN)
  TARGET_LINK_LIBRARIES(testngppst-runner-lib dl)
ELSEIF(TESTNGPPST_USE_LTDL)
  TARGET_LINK_LIBRARIES(testngppst-runner-lib ltdl)
ELSEIF(TESTNGPPST_USE_LOADLIBRARY)
ELSE(TESTNGPPST_USE_DLOPEN)
  MESSAGE(FATAL_ERROR "No module loader found")
ENDIF(TESTNGPPST_USE_DLOPEN)

INSTALL(
   TARGETS testngppst-runner
   RUNTIME DESTINATION bin)

