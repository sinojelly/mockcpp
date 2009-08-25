
TESTCPP_INCLUDE_PATH = $(top_builddir)/include/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include 

noinst_LTLIBRARIES = libtestcpp.la

libtestcpp_la_LDFLAGS = \
  -export-dynamic

libtestcpp_la_SOURCES = \
  AssertionFailure.cpp \
  TestSuiteDesc.cpp \
  ResourceCheckPoint.cpp \
  Formatter.cpp \
  TypeString.cpp

