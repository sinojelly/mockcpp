
TESTCPP_INCLUDE_PATH = $(top_builddir)/include/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include 
AM_LDFLAGS = -export-dynamic -no-undefined

noinst_LTLIBRARIES = libtestcpp.la 

libtestcpp_la_SOURCES = \
  AssertionFailure.cpp \
  TestSuiteDesc.cpp \
  TypeString.cpp \
  Formatter.cpp \
  ResourceCheckPoint.cpp \
  OptionList.cpp
