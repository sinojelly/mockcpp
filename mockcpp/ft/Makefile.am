
THIRD_PARTY_ROOT = $(top_builddir)/3rdparty
TESTCPP_ROOT = $(THIRD_PARTY_ROOT)/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include \
              -I$(THIRD_PARTY_ROOT) \
              -I$(TESTCPP_ROOT)/include

TARGET_SRC = mockcpp-ft.cpp

noinst_LTLIBRARIES = libmockcpp-ft.la

libmockcpp_ft_la_SOURCES = $(TARGET_SRC)
CLEANFILES = $(TARGET_SRC)
libmockcpp_ft_la_LIBADD = $(top_srcdir)/src/libmockcpp.la 
libmockcpp_ft_la_LDFLAGS = \
  -module \
  -rpath /dev/null


UTCG = $(PYTHON) $(TESTCPP_ROOT)/scripts/testcppgen.py 

TESTSUITES = \
  TestServiceUser.h

$(TARGET_SRC) : $(TESTSUITES)
	$(UTCG) -o $@ $^
