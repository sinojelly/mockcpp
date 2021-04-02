INCLUDE(${PROJECT_SOURCE_DIR}/../../../tools/testngpp.cmake)

ADD_DEFINITIONS(
    -DPACKAGE_NAME=${PACKAGE_NAME}
    -DPACKAGE_STRING=${PACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
)

SET(TESTNGPP_LIBRARY testngpp-except testngpp-utils mem-checker)

IF(CMAKE_SYSTEM_NAME MATCHES Linux)
  IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_MODULE_LINKER_FLAGS "-Wl,--fatal-warnings -Wl,--no-undefined")
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDIF()

SET(STDOUTLISTENER_SRCS
  StdoutTestListener.cpp
)

SET(XMLLISTENER_SRCS
  XMLTestListener.cpp
  XMLBuilder.cpp
)

IF(UNIX AND NOT CYGWIN)
ADD_DEFINITIONS(
    -fPIC
)
ENDIF(UNIX AND NOT CYGWIN)

IF(UNIX OR MINGW)
ADD_DEFINITIONS(
    -g -ggdb
)
ENDIF(UNIX OR MINGW)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/src ${CMAKE_BINARY_DIR}/src/utils ${CMAKE_BINARY_DIR}/src/mem_checker)

ADD_LIBRARY(testngppstdoutlistener MODULE ${STDOUTLISTENER_SRCS})
ADD_LIBRARY(testngppxmllistener MODULE ${XMLLISTENER_SRCS})

ADD_LIBRARY(testngppxmllistener-fortest STATIC ${XMLLISTENER_SRCS})
TARGET_LINK_LIBRARIES(testngppxmllistener-fortest ${TESTNGPP_LIBRARY})

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/include .)

IF(NOT MSVC AND NOT MINGW)
 SET_TARGET_PROPERTIES(
   testngppstdoutlistener 
   testngppxmllistener
   PROPERTIES SUFFIX ".so")
ENDIF(NOT MSVC AND NOT MINGW)

TARGET_LINK_LIBRARIES(testngppstdoutlistener ${TESTNGPP_LIBRARY})
TARGET_LINK_LIBRARIES(testngppxmllistener ${TESTNGPP_LIBRARY})

INSTALL(
   TARGETS testngppstdoutlistener testngppxmllistener
   LIBRARY DESTINATION binary/${TESTNGPP_OS_COMPILER}/testngpp/listener)

IF(MSVC)
  INSTALL(
   FILES ${CMAKE_BINARY_DIR}/src/listeners/Debug/testngppstdoutlistener.pdb ${CMAKE_BINARY_DIR}/src/listeners/Debug/testngppxmllistener.pdb
   DESTINATION binary/${TESTNGPP_OS_COMPILER}/testngpp/listener)
ENDIF(MSVC)   

