
ADD_DEFINITIONS(
    -DPACKAGE_NAME=${PACKAGE_NAME}
    -DPACKAGE_STRING=${PACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
)

SET(TESTNGPPST_LIBRARY testngppst-except testngppst-utils mem-checker)

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

IF(UNIX)
ADD_DEFINITIONS(
    -g -ggdb
)
ENDIF(UNIX)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/src ${CMAKE_BINARY_DIR}/src/utils ${CMAKE_BINARY_DIR}/src/mem_checker)

ADD_LIBRARY(testngppststdoutlistener MODULE ${STDOUTLISTENER_SRCS})
ADD_LIBRARY(testngppstxmllistener MODULE ${XMLLISTENER_SRCS})

ADD_LIBRARY(testngppstxmllistener-fortest STATIC ${XMLLISTENER_SRCS})
TARGET_LINK_LIBRARIES(testngppstxmllistener-fortest ${TESTNGPPST_LIBRARY})

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/include .)

IF(NOT MSVC)
 SET_TARGET_PROPERTIES(
   testngppststdoutlistener 
   testngppstxmllistener
   PROPERTIES SUFFIX ".so")
ENDIF(NOT MSVC)

TARGET_LINK_LIBRARIES(testngppststdoutlistener ${TESTNGPPST_LIBRARY})
TARGET_LINK_LIBRARIES(testngppstxmllistener ${TESTNGPPST_LIBRARY})

INSTALL(
   TARGETS testngppststdoutlistener testngppstxmllistener
   LIBRARY DESTINATION testngppst/listener)

