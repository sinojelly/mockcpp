
CXXTEST_ROOT = $(top_builddir)/3rdparty/cxxtest

AM_CPPFLAGS = -I$(top_builddir)/include \
              -I$(top_builddir)/3rdparty \
              -I$(CXXTEST_ROOT)

lib_LTLIBRARIES = libmockcpp-ut.la

libmockcpp_ut_la_SOURCES = mockcpp-ut.cpp
CLEANFILES = mockcpp-ut.cpp
libmockcpp_ut_la_LIBADD = $(top_srcdir)/src/libmockcpp.la 

UTCG = testcppgen

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
 TestIsStringStartWith.h \
 TestIsStringEndWith.h \
 TestIsStringContains.h \
 TestChainableMockMethodNameKey.h \
 TestChainableMockMethodContainer.h \
 TestStringConstraint.h \
 TestIncrementStub.h

mockcpp-ut.cpp : $(TESTSUITES)
	$(UTCG) -o $@ $^
