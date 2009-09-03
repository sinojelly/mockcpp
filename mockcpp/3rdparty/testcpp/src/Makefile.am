
TESTCPP_INCLUDE_PATH = $(top_builddir)/include/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include 
AM_LDFLAGS = -export-dynamic -no-undefined

noinst_LTLIBRARIES = libtestcpp.la libtestcpprcp.la

libtestcpp_la_SOURCES = \
  AssertionFailure.cpp \
  TestSuiteDesc.cpp \
  TypeString.cpp \
  Formatter.cpp \
  OptionList.cpp

libtestcpprcp_la_SOURCES = \
  ResourceCheckPoint.cpp 
