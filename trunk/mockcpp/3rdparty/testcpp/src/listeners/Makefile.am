
TESTCPP_INCLUDE_PATH = $(top_builddir)/include/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include

noinst_LTLIBRARIES = libtestcppstdoutlistener.la libtestcppxmllistener.la

libtestcppstdoutlistener_la_LDFLAGS = \
  -module \
  -rpath /dev/null

libtestcppstdoutlistener_la_SOURCES= StdoutTestListener.cpp

libtestcppxmllistener_la_LDFLAGS = \
  -module \
  -rpath /dev/null

libtestcppxmllistener_la_SOURCES= XMLTestListener.cpp
