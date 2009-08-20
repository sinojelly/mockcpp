
THIRD_PARTY_ROOT = $(top_builddir)/3rdparty
TESTCPP_ROOT = $(THIRD_PARTY_ROOT)/testcpp

AM_CPPFLAGS = -I$(top_builddir)/include \
              -I$(THIRD_PARTY_ROOT) \
              -I$(TESTCPP_ROOT)/include

TARGET_SRC1 = mockcpp-ut1.cpp
TARGET_SRC2 = mockcpp-ut2.cpp
TARGET_SRC3 = mockcpp-ut3.cpp
TARGET_SRC4 = mockcpp-ut4.cpp
TARGET_SRC5 = mockcpp-ut5.cpp

lib_LTLIBRARIES = \
 libmockcpp-ut1.la \
 libmockcpp-ut2.la \
 libmockcpp-ut3.la \
 libmockcpp-ut4.la \
 libmockcpp-ut5.la

libmockcpp_ut1_la_SOURCES = $(TARGET_SRC1)
libmockcpp_ut2_la_SOURCES = $(TARGET_SRC2)
libmockcpp_ut3_la_SOURCES = $(TARGET_SRC3)
libmockcpp_ut4_la_SOURCES = $(TARGET_SRC4)
libmockcpp_ut5_la_SOURCES = $(TARGET_SRC5)

CLEANFILES = \
 $(TARGET_SRC1) \
 $(TARGET_SRC2) \
 $(TARGET_SRC3) \
 $(TARGET_SRC4) \
 $(TARGET_SRC5)

libmockcpp_ut1_la_LIBADD = $(top_srcdir)/src/libmockcpp.la
libmockcpp_ut2_la_LIBADD = $(top_srcdir)/src/libmockcpp.la
libmockcpp_ut3_la_LIBADD = $(top_srcdir)/src/libmockcpp.la
libmockcpp_ut4_la_LIBADD = $(top_srcdir)/src/libmockcpp.la
libmockcpp_ut5_la_LIBADD = $(top_srcdir)/src/libmockcpp.la

libmockcpp_ut1_la_LDFLAGS = -module
libmockcpp_ut2_la_LDFLAGS = -module
libmockcpp_ut3_la_LDFLAGS = -module
libmockcpp_ut4_la_LDFLAGS = -module
libmockcpp_ut5_la_LDFLAGS = -module

UTCG = $(PYTHON) $(TESTCPP_ROOT)/scripts/testcppgen.py

TESTSUITES1 = \
 TestAny.h \
 TestHolder.h \
 TestIsEqual.h \
 TestFormatter.h \
 TestConstraintSet.h \
 TestReturnObjectList.h \
 TestInterfaceInfo.h

TESTSUITES2 = \
 TestChainableObject.h \
 TestInvocation.h \
 TestInvocationMocker.h \
 TestMethodInfoReader.h \
 TestDelegatedMethod.h 

TESTSUITES3 = \
 TestVirtualTable.h \
 TestStubContainter.h \
 TestIsStringStartWith.h \
 TestIsStringEndWith.h 

TESTSUITES4 = \
 TestIsStringContains.h \
 TestChainableMockMethodNameKey.h \
 TestChainableMockMethodContainer.h \
 TestStringConstraint.h \
 TestIncrementStub.h

TESTSUITES5 = \
 TestMockObject.h 

$(TARGET_SRC1) : $(TESTSUITES1)
	$(UTCG) -o $@ $^

$(TARGET_SRC2) : $(TESTSUITES2)
	$(UTCG) -o $@ $^

$(TARGET_SRC3) : $(TESTSUITES3)
	$(UTCG) -o $@ $^

$(TARGET_SRC4) : $(TESTSUITES4)
	$(UTCG) -o $@ $^

$(TARGET_SRC5) : $(TESTSUITES5)
	$(UTCG) -o $@ $^
