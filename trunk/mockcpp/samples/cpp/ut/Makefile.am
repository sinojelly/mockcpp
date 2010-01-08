
THIRD_PARTY_ROOT = $(top_builddir)/3rdparty
CXXTESTPLUS_ROOT = $(THIRD_PARTY_ROOT)/cxxtestplus

AM_CPPFLAGS = \
  -I$(top_builddir)/include \
  -I$(THIRD_PARTY_ROOT) \
  -I$(CXXTESTPLUS_ROOT)/include \
  -I$(top_builddir)/samples/cpp/include 

if USE_TEST_TARGET
   MOCKCPP_LIB_FOR_TEST = \
     $(top_builddir)/src/libmockcpp-for-test.la
else
   MOCKCPP_LIB_FOR_TEST = \
     $(top_builddir)/src/libmockcpp.la \
     $(top_builddir)/3rdparty/cxxtestplus/src/libcxxtestplus.la
endif


AM_LDFLAGS = \
  -module \
  -dynamic \
  -no-undefined \
  -rpath /dev/null \
  $(MOCKCPP_LIB_FOR_TEST) \
  $(top_builddir)/samples/cpp/src/libsample.la 


TARGET_SRC = sample-ut.cpp

noinst_LTLIBRARIES = \
 libsample-ut.la 

libsample_ut_la_SOURCES = $(TARGET_SRC)

CLEANFILES = \
 $(TARGET_SRC) 

UTCG = $(PYTHON) $(CXXTESTPLUS_ROOT)/scripts/cxxtestplus-gen.py

TESTSUITES = \
   TestCompositeChecker.h

$(TARGET_SRC) : $(TESTSUITES)
	$(UTCG) -o $@ $^

