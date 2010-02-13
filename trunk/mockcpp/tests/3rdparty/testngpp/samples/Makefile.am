
AM_CPPFLAGS = -I$(top_builddir)/include 

noinst_LTLIBRARIES = libfoo.la
CLEANFILES=TestFoo.cpp

libfoo_la_SOURCES = \
  TestFoo.cpp

libfoo_la_LDFLAGS = \
  -module \
  -no-undefined \
  -rpath /dev/null 

libfoo_la_LIBADD = $(top_builddir)/src/libtestngpp.la

TestFoo.cpp : TestFoo.h
	$(PYTHON) $(top_builddir)/scripts/testngppgen3.py -o $@ $<
