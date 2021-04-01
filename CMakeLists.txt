
CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.19)

PROJECT(mockcpp)

INCLUDE(ProjectVar.txt)

ADD_SUBDIRECTORY(src)

INSTALL(DIRECTORY include/mockcpp DESTINATION include
        PATTERN ".svn" EXCLUDE)

INSTALL(DIRECTORY 3rdparty/fake_boost DESTINATION include
        PATTERN ".svn" EXCLUDE)

INSTALL(DIRECTORY 3rdparty/msinttypes DESTINATION include
        PATTERN ".svn" EXCLUDE)

SET(MOCKCPP_XUNIT "testngpp" CACHE STRING "Set to gtest/cpputest/cppunit to use other testframeworks.")


