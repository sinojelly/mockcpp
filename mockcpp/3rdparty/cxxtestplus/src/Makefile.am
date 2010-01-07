
CXXTESTPLUS_INCLUDE_PATH = $(top_builddir)/include/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include 
AM_LDFLAGS = -export-dynamic -no-undefined 

lib_LTLIBRARIES = libcxxtestplus.la

libcxxtestplus_la_SOURCES = \
  AssertionFailure.cpp \
  TestSuiteDesc.cpp \
  ResourceCheckPoint.cpp \
  TypeString.cpp \
  Formatter.cpp \
  OptionList.cpp \
  StringToOptions.cpp 

pkginclude_HEADERS = \
  $(CXXTESTPLUS_INCLUDE_PATH)/testcpp.hpp \
  $(CXXTESTPLUS_INCLUDE_PATH)/testcpp.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/Asserter.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/Error.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/AssertionFailure.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/TestFixture.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/ResourceCheckPoint.h 


internaldir = $(pkgincludedir)/internal

internal_HEADERS = \
  $(CXXTESTPLUS_INCLUDE_PATH)/internal/TestCase.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/internal/TestFixtureDesc.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/internal/TestSuiteDesc.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/internal/TestCaseInfoReader.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/internal/TestSuiteInfoReader.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/internal/TestFixtureInfoReader.h

utilsdir = $(pkgincludedir)/utils

utils_HEADERS = \
  $(CXXTESTPLUS_INCLUDE_PATH)/utils/TypeString.h \
  $(CXXTESTPLUS_INCLUDE_PATH)/utils/Formatter.h  \
  $(CXXTESTPLUS_INCLUDE_PATH)/utils/OptionList.h  

