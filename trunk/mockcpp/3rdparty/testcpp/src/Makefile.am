
TESTCPP_INCLUDE_PATH = $(top_builddir)/include/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include 

lib_LTLIBRARIES = libtestcpp.la
libtestcpp_la_LDFLAGS = -export-dynamic

libtestcpp_la_SOURCES = \
  AssertionFailure.cpp \
  TestSuiteDesc.cpp \
  ResourceCheckPoint.cpp

pkginclude_HEADERS = \
  $(TESTCPP_INCLUDE_PATH)/testcpp.hpp \
  $(TESTCPP_INCLUDE_PATH)/testcpp.h \
  $(TESTCPP_INCLUDE_PATH)/Asserter.h \
  $(TESTCPP_INCLUDE_PATH)/Error.h \
  $(TESTCPP_INCLUDE_PATH)/AssertionFailure.h \
  $(TESTCPP_INCLUDE_PATH)/TestFixture.h \
  $(TESTCPP_INCLUDE_PATH)/ResourceCheckPoint.h 

internaldir = $(pkgincludedir)/internal

internal_HEADERS = \
  $(TESTCPP_INCLUDE_PATH)/internal/TestCase.h \
  $(TESTCPP_INCLUDE_PATH)/internal/TestFixtureDesc.h \
  $(TESTCPP_INCLUDE_PATH)/internal/TestSuiteDesc.h \
  $(TESTCPP_INCLUDE_PATH)/internal/TestCaseInfoReader.h \
  $(TESTCPP_INCLUDE_PATH)/internal/TestSuiteInfoReader.h \
  $(TESTCPP_INCLUDE_PATH)/internal/TestFixtureInfoReader.h
