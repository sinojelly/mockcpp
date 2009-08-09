
AM_CPPFLAGS = -I$(top_builddir)/include -I$(top_builddir)/3rdparty

lib_LTLIBRARIES = libmockcpp.la

EXTRA_HEADERS = \
 $(top_builddir)/include/DelegatedMethodDef.h \
 $(top_builddir)/include/DelegatedMethodGetDef.h \
 $(top_builddir)/include/DelegatedMethodGetByVptrDef.h \
 $(top_builddir)/include/ArgumentListDef.h  \
 $(top_builddir)/include/MethodTypeTraitsDef.h

BUILT_SOURCES = $(EXTRA_HEADERS)
CLEANFILES = $(EXTRA_HEADERS)

libmockcpp_la_SOURCES = \
 AfterMatcher.cpp \
 AnyBase.cpp \
 Any.cpp \
 Asserter.cpp \
 AssertionFailedError.cpp \
 BeforeMatcher.cpp \
 CallerMatcher.cpp \
 ChainableMockMethodCore.cpp \
 ChainableMockObjectBase.cpp \
 ChainableMockObject.cpp \
 MockObjectBase.cpp \
 ChainingMockHelper.cpp \
 ConstraintSet.cpp \
 DecoratedConstraint.cpp \
 DefaultMatcher.cpp \
 DefaultStub.cpp \
 RepeatStub.cpp \
 Exception.cpp \
 ExpectsMatcher.cpp \
 Formatter.cpp \
 GlobalMockObject.cpp \
 IdentityBuilder.cpp \
 IgnoreResultHandler.cpp \
 IgnoreResultHandlerFactory.cpp \
 IgnoreReturnStub.cpp \
 Invocation.cpp \
 InvocationId.cpp \
 InvocationMocker.cpp \
 InvocationMockerSet.cpp \
 InvocationTimesMatcher.cpp \
 InvokedAtLeast.cpp \
 InvokedAtMost.cpp \
 InvokedExactly.cpp \
 InvokedOnce.cpp \
 InvokedTimesMatcher.cpp \
 IsAnythingHelper.cpp \
 MismatchResultHandler.cpp \
 MismatchResultHandlerFactory.cpp \
 NormalResultHandler.cpp \
 NormalResultHandlerFactory.cpp \
 InvocationMockBuilderGetter.cpp \
 OutBoundPointer.cpp \
 PendingMatcher.cpp \
 ProcStub.cpp \
 RefAny.cpp \
 Result.cpp \
 ReturnObjectList.cpp \
 ReturnStub.cpp \
 SimpleInvocationRecorder.cpp \
 StubsMatcher.cpp \
 TestFailureMatcher.cpp \
 TypelessConstraintAdapter.cpp \
 TypelessStubAdapter.cpp \
 TypeString.cpp \
 VoidResultHandler.cpp \
 VoidResultHandlerFactory.cpp \
 WillStub.cpp \
 ThenStub.cpp \
 VirtualTable.cpp \
 ChainableMockMethodContainer.cpp \
 ChainableMockMethodNameKey.cpp \
 ChainableMockMethodIndexKey.cpp \
 StubContainer.cpp \
 StringConstraint.cpp \
 IsStringStartWith.cpp \
 IsStringEndWith.cpp \
 IsStringContains.cpp \
 MemoryCheckPoint.cpp \
 DelegatedMethodGetter.cpp \
 DieStub.cpp

ALLOW_MI = @MOCKCPP_ALLOW_MI@
MAX_INHERITANCE = @MOCKCPP_MI@
MAX_VTBL_SIZE = @MOCKCPP_MVS@
MAX_PARAMETERS = @MOCKCPP_MAX_PARAMS@

EXTRA_VTBL_HEADERS_DEFS = --allow-mi=$(ALLOW_MI) --max-inheritance=$(MAX_INHERITANCE) \
                        --max-vtbl-size=$(MAX_VTBL_SIZE) --include-path=$(top_builddir)/include

EXTRA_PARAMS_HEADERS_DEFS = --max-parameters=$(MAX_PARAMETERS) --include-path=$(top_builddir)/include


$(top_builddir)/include/DelegatedMethodDef.h: FORCE
	$(PYTHON) $(top_builddir)/src/generate_vtbl_related_files.py $(EXTRA_VTBL_HEADERS_DEFS)

$(top_builddir)/include/DelegatedMethodGetByVptrDef.h: FORCE
	$(PYTHON) $(top_builddir)/src/generate_arg_related_files.py $(EXTRA_PARAMS_HEADERS_DEFS)

FORCE:
