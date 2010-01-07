
CXXTESTPLUS_INCLUDE_PATH = $(top_builddir)/include/testcpp

AM_CPPFLAGS = \
  -I$(top_builddir)/include

AM_LDFLAGS = \
  -module \
  -rpath /dev/null \
  -no-undefined \
  $(top_builddir)/src/libcxxtestplus.la

noinst_LTLIBRARIES = \
  libcxxtestplus_stdout_listener.la \
  libcxxtestplus_xml_listener.la

libcxxtestplus_stdout_listener_la_SOURCES = \
  StdoutTestListener.cpp

libcxxtestplus_xml_listener_la_SOURCES = \
  XMLTestListener.cpp \
  XMLBuilder.cpp
