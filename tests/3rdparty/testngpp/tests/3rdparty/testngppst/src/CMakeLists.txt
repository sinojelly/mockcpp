
IF(MSVC)
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
ENDIF(MSVC)

SET(TESTNGPPST_SRCS
  except/Exception.cpp
  except/AssertionFailure.cpp 
  TestFixture.cpp
  TestSuiteDesc.cpp 
  TypeString.cpp 
  Formatter.cpp 
  MemChecker.cpp
  TestCase.cpp
  mem_checker/bool_array.cpp       
  mem_checker/mem_pool_base.cpp
  mem_checker/debug_new.cpp        
  mem_checker/static_mem_pool.cpp
  mem_checker/interface_4xunit.cpp
  mem_checker/reporter.cpp
  mem_checker/check_status.cpp
  mem_checker/NoThrowsReporter.cpp
)

IF (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # using regular Clang or AppleClang
  SET(TESTNGPP_SRCS ${TESTNGPP_SRCS} runner/ResourceCheckPoint.cpp)
ENDIF()

# include debug info in testngppst.lib
IF(MSVC)
	ADD_DEFINITIONS( /Z7 )
ENDIF(MSVC)

IF(WIN32)
  ADD_LIBRARY(testngppst STATIC ${TESTNGPPST_SRCS})
ELSE(WIN32)  
  ADD_LIBRARY(testngppst SHARED ${TESTNGPPST_SRCS})
ENDIF(WIN32)

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

# can not link to other lib in cmake 
#TARGET_LINK_LIBRARIES(mem-checker)
#LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/src/mem_checker)

ADD_DEFINITIONS(-D__STDC_FORMAT_MACROS)

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/3rdparty)
IF(MSVC)
INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/../../../3rdparty/msinttypes)
ENDIF(MSVC)

IF(WIN32)
  INSTALL(
   TARGETS testngppst
   ARCHIVE DESTINATION lib)
ELSE(WIN32)  
  INSTALL(
   TARGETS testngppst
   LIBRARY DESTINATION lib)
ENDIF(WIN32)

   


