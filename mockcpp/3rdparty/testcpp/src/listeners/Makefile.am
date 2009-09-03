
TESTCPP_INCLUDE_PATH = $(top_builddir)/include/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include
AM_LDFLAGS = \
 -module \
 -rpath /dev/null \
 -no-undefined \
 $(top_builddir)/src/libtestcpp.la 

noinst_LTLIBRARIES = libtestcppstdoutlistener.la libtestcppxmllistener.la

libtestcppstdoutlistener_la_SOURCES= StdoutTestListener.cpp
libtestcppxmllistener_la_SOURCES= XMLTestListener.cpp
