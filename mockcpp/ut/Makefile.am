
THIRD_PARTY_ROOT = $(top_builddir)/3rdparty
TESTCPP_ROOT = $(THIRD_PARTY_ROOT)/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include \
              -I$(THIRD_PARTY_ROOT) \
              -I$(TESTCPP_ROOT)/include

TARGET_SRC = mockcpp-ut.cpp

lib_LTLIBRARIES = libmockcpp-ut.la

libmockcpp_ut_la_SOURCES = $(TARGET_SRC)
CLEANFILES = $(TARGET_SRC)
libmockcpp_ut_la_LIBADD = $(top_srcdir)/src/libmockcpp.la
libmockcpp_ut_la_LDFLAGS = -module

UTCG = $(PYTHON) $(TESTCPP_ROOT)/scripts/testcppgen.py

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

$(TARGET_SRC) : $(TESTSUITES)
	$(UTCG) -o $@ $^
