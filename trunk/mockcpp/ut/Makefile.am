
CXXTEST_ROOT = $(top_builddir)/3rdparty/cxxtest

AM_CPPFLAGS = -I$(top_builddir)/include \
              -I$(top_builddir)/3rdparty \
              -I$(CXXTEST_ROOT)

noinst_PROGRAMS = mockcpp-ut

nodist_mockcpp_ut_SOURCES = mockcpp-ut.cpp
CLEANFILES = mockcpp-ut.cpp
mockcpp_ut_LDADD = $(top_builddir)/libs/libcxxtest.la $(top_srcdir)/src/libmockcpp.la

UTCG = $(CXXTEST_ROOT)/cxxtestgen.pl

TESTSUITES = \
 TestAny.h \
 TestHolder.h \
 TestIsEqual.h \
 TestFormatter.h \
 TestConstraintSet.h \
 TestReturnObjectList.h \
 TestChainableObject.h \
 TestInvocation.h \
 TestInvocationMocker.h \
 TestMethodInfoReader.h \
 TestDelegatedMethod.h \
 TestVirtualTable.h \
 TestMockObject.h \
 TestStubContainter.h \
 TestChainableMockMethodNameKey.h \
 TestChainableMockMethodContainer.h

mockcpp-ut.cpp : $(TESTSUITES)
	$(UTCG) --have-eh --have-std --part -o $@ $^
