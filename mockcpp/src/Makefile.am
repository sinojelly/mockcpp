
MOCKCPP_SRC_PATH=$(top_builddir)/src
MOCKCPP_INCLUDE_PATH = $(top_builddir)/include
MOCKCPP_HEADERS_PATH = $(top_builddir)/include/mockcpp

AM_CPPFLAGS = \
 -I$(MOCKCPP_INCLUDE_PATH) \
 -I$(top_builddir)/3rdparty \
 -Wall

if USE_TEST_TARGET
noinst_LTLIBRARIES = libmockcpp-for-test.la
libmockcpp_for_test_la_LDFLAGS = \
   @MOCKCPP_LDFLAGS_FOR_DIST@ \
   ../3rdparty/testcpp/src/libtestcpp.la \
   -rpath /dev/null 
endif

lib_LTLIBRARIES = libmockcpp.la
libmockcpp_la_LDFLAGS = @MOCKCPP_LDFLAGS_FOR_DIST@ 

ARG_RELATED_HEADER_FILES =  \
 $(MOCKCPP_HEADERS_PATH)/DelegatedMethodDef.h \
 $(MOCKCPP_HEADERS_PATH)/ArgumentsListDef.h  \
 $(MOCKCPP_HEADERS_PATH)/MethodTypeTraitsDef.h

VBTL_RELATED_HEADER_FILES = \
 $(MOCKCPP_HEADERS_PATH)/DelegatedMethodGetDef.h \
 $(MOCKCPP_HEADERS_PATH)/DelegatedMethodGetByVptrDef.h \
 $(MOCKCPP_HEADERS_PATH)/GenericMethodCheckerDef.h \
 $(MOCKCPP_HEADERS_PATH)/DestructorAddrGetterDef.h \
 $(MOCKCPP_HEADERS_PATH)/DestructorCheckerDef.h

EXTRA_HEADERS = \
 $(ARG_RELATED_HEADER_FILES) \
 $(VBTL_RELATED_HEADER_FILES)

pkginclude_HEADERS= \
  $(ARG_RELATED_HEADER_FILES)  \
  $(VBTL_RELATED_HEADER_FILES) \
  $(MOCKCPP_HEADERS_PATH)/AfterMatchBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/AfterMatchBuilder.tcc \
  $(MOCKCPP_HEADERS_PATH)/AfterMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/types/Any.h \
  $(MOCKCPP_HEADERS_PATH)/types/AnyBase.h \
  $(MOCKCPP_HEADERS_PATH)/ArgumentsList.h \
  $(MOCKCPP_HEADERS_PATH)/ArgumentsMacroHelpers.h \
  $(MOCKCPP_HEADERS_PATH)/ArgumentsMatchBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/ArgumentsMatchBuilder.tcc \
  $(MOCKCPP_HEADERS_PATH)/Asserter.h \
  $(MOCKCPP_HEADERS_PATH)/AssertionFailedError.h \
  $(MOCKCPP_HEADERS_PATH)/BeforeMatchBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/BeforeMatchBuilder.tcc \
  $(MOCKCPP_HEADERS_PATH)/BeforeMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/CallerMatchBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/CallerMatchBuilder.tcc \
  $(MOCKCPP_HEADERS_PATH)/CallerMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/ChainableMockMethod.h \
  $(MOCKCPP_HEADERS_PATH)/ChainableMockMethodContainer.h \
  $(MOCKCPP_HEADERS_PATH)/ChainableMockMethodCore.h \
  $(MOCKCPP_HEADERS_PATH)/ChainableMockMethodIndexKey.h \
  $(MOCKCPP_HEADERS_PATH)/ChainableMockMethodKey.h \
  $(MOCKCPP_HEADERS_PATH)/ChainableMockMethodNameKey.h \
  $(MOCKCPP_HEADERS_PATH)/ChainableMockObject.h \
  $(MOCKCPP_HEADERS_PATH)/ChainableMockObjectBase.h \
  $(MOCKCPP_HEADERS_PATH)/ChainingMockHelper.h \
  $(MOCKCPP_HEADERS_PATH)/Constraint.h \
  $(MOCKCPP_HEADERS_PATH)/ConstraintSet.h \
  $(MOCKCPP_HEADERS_PATH)/DecoratedConstraint.h \
  $(MOCKCPP_HEADERS_PATH)/DefaultBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/DefaultMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/DefaultStub.h \
  $(MOCKCPP_HEADERS_PATH)/DelegatedMethod.h \
  $(MOCKCPP_HEADERS_PATH)/DelegatedMethodGetter.h \
  $(MOCKCPP_HEADERS_PATH)/DieStub.h \
  $(MOCKCPP_HEADERS_PATH)/DestructorChecker.h \
  $(MOCKCPP_HEADERS_PATH)/DummyBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/EqualityUtil.h \
  $(MOCKCPP_HEADERS_PATH)/Exception.h \
  $(MOCKCPP_HEADERS_PATH)/ExpectsMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/Formatter.h \
  $(MOCKCPP_HEADERS_PATH)/Functor.h \
  $(MOCKCPP_HEADERS_PATH)/GlobalMockObject.h \
  $(MOCKCPP_HEADERS_PATH)/GnuMethodInfoReader.h \
  $(MOCKCPP_HEADERS_PATH)/types/Holder.h \
  $(MOCKCPP_HEADERS_PATH)/IdentityBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/Ignore.h \
  $(MOCKCPP_HEADERS_PATH)/IgnoreHandler.h \
  $(MOCKCPP_HEADERS_PATH)/IgnoreResultHandler.h \
  $(MOCKCPP_HEADERS_PATH)/IgnoreResultHandlerFactory.h \
  $(MOCKCPP_HEADERS_PATH)/IgnoreReturnStub.h \
  $(MOCKCPP_HEADERS_PATH)/IncrementStub.h \
  $(MOCKCPP_HEADERS_PATH)/IndexInvokableGetter.h \
  $(MOCKCPP_HEADERS_PATH)/InterfaceInfo.h \
  $(MOCKCPP_HEADERS_PATH)/Invocation.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationId.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationMockBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationMockBuilder.tcc \
  $(MOCKCPP_HEADERS_PATH)/InvocationMockBuilderGetter.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationMocker.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationMockerContainer.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationMockerNamespace.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationMockerSet.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationTimesMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/InvocationWithReturnType.h \
  $(MOCKCPP_HEADERS_PATH)/Invokable.h \
  $(MOCKCPP_HEADERS_PATH)/InvokedAtLeast.h \
  $(MOCKCPP_HEADERS_PATH)/InvokedAtMost.h \
  $(MOCKCPP_HEADERS_PATH)/InvokedExactly.h \
  $(MOCKCPP_HEADERS_PATH)/InvokedOnce.h \
  $(MOCKCPP_HEADERS_PATH)/InvokedTimesMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/InvokedTimesReader.h \
  $(MOCKCPP_HEADERS_PATH)/InvokedTimesRecorder.h \
  $(MOCKCPP_HEADERS_PATH)/IsAnything.h \
  $(MOCKCPP_HEADERS_PATH)/IsAnythingHelper.h \
  $(MOCKCPP_HEADERS_PATH)/IsConst.h \
  $(MOCKCPP_HEADERS_PATH)/IsEqual.h \
  $(MOCKCPP_HEADERS_PATH)/IsMirror.h \
  $(MOCKCPP_HEADERS_PATH)/IsNotEqual.h \
  $(MOCKCPP_HEADERS_PATH)/IsRef.h \
  $(MOCKCPP_HEADERS_PATH)/IsStringContains.h \
  $(MOCKCPP_HEADERS_PATH)/IsStringEndWith.h \
  $(MOCKCPP_HEADERS_PATH)/IsStringStartWith.h \
  $(MOCKCPP_HEADERS_PATH)/Matcher.h \
  $(MOCKCPP_HEADERS_PATH)/Method.h \
  $(MOCKCPP_HEADERS_PATH)/MethodInfoReader.h \
  $(MOCKCPP_HEADERS_PATH)/MethodTypeTraits.h \
  $(MOCKCPP_HEADERS_PATH)/MismatchResultHandler.h \
  $(MOCKCPP_HEADERS_PATH)/MismatchResultHandlerFactory.h \
  $(MOCKCPP_HEADERS_PATH)/MockObject.h \
  $(MOCKCPP_HEADERS_PATH)/MockObjectBase.h \
  $(MOCKCPP_HEADERS_PATH)/MoreStubBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/MoreStubBuilder.tcc \
  $(MOCKCPP_HEADERS_PATH)/NormalResultHandler.h \
  $(MOCKCPP_HEADERS_PATH)/NormalResultHandlerFactory.h \
  $(MOCKCPP_HEADERS_PATH)/OrderingMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/OutBound.h \
  $(MOCKCPP_HEADERS_PATH)/OutBoundPointer.h \
  $(MOCKCPP_HEADERS_PATH)/OutputStringStream.h \
  $(MOCKCPP_HEADERS_PATH)/PendingMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/types/PlaceHolder.h \
  $(MOCKCPP_HEADERS_PATH)/ProcStub.h \
  $(MOCKCPP_HEADERS_PATH)/types/RefAny.h \
  $(MOCKCPP_HEADERS_PATH)/types/RefHolder.h \
  $(MOCKCPP_HEADERS_PATH)/RepeatMacros.h \
  $(MOCKCPP_HEADERS_PATH)/RepeatStub.h \
  $(MOCKCPP_HEADERS_PATH)/Result.h \
  $(MOCKCPP_HEADERS_PATH)/ResultHandler.h \
  $(MOCKCPP_HEADERS_PATH)/ResultHandlerFactory.h \
  $(MOCKCPP_HEADERS_PATH)/ReturnObjectList.h \
  $(MOCKCPP_HEADERS_PATH)/ReturnStub.h \
  $(MOCKCPP_HEADERS_PATH)/SelfDescribe.h \
  $(MOCKCPP_HEADERS_PATH)/SimpleInvocationRecorder.h \
  $(MOCKCPP_HEADERS_PATH)/StatelessMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/StringConstraint.h \
  $(MOCKCPP_HEADERS_PATH)/StringPredict.h \
  $(MOCKCPP_HEADERS_PATH)/Stub.h \
  $(MOCKCPP_HEADERS_PATH)/StubBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/StubBuilder.tcc \
  $(MOCKCPP_HEADERS_PATH)/StubContainer.h \
  $(MOCKCPP_HEADERS_PATH)/StubsMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/TestFailureMatcher.h \
  $(MOCKCPP_HEADERS_PATH)/ThenStub.h \
  $(MOCKCPP_HEADERS_PATH)/ThrowExceptionStub.h \
  $(MOCKCPP_HEADERS_PATH)/TypeString.h \
  $(MOCKCPP_HEADERS_PATH)/TypeTraits.h \
  $(MOCKCPP_HEADERS_PATH)/TypelessConstraint.h \
  $(MOCKCPP_HEADERS_PATH)/TypelessConstraintAdapter.h \
  $(MOCKCPP_HEADERS_PATH)/TypelessStub.h \
  $(MOCKCPP_HEADERS_PATH)/TypelessStubAdapter.h \
  $(MOCKCPP_HEADERS_PATH)/types/ValueHolder.h \
  $(MOCKCPP_HEADERS_PATH)/VirtualTable.h \
  $(MOCKCPP_HEADERS_PATH)/VirtualTableUtils.h \
  $(MOCKCPP_HEADERS_PATH)/Void.h \
  $(MOCKCPP_HEADERS_PATH)/VoidResultHandler.h \
  $(MOCKCPP_HEADERS_PATH)/VoidResultHandlerFactory.h \
  $(MOCKCPP_HEADERS_PATH)/WillStub.h \
  $(MOCKCPP_HEADERS_PATH)/WorkingBuilder.h \
  $(MOCKCPP_HEADERS_PATH)/mockable.h \
  $(MOCKCPP_HEADERS_PATH)/mockcpp.h \
  $(MOCKCPP_HEADERS_PATH)/mockcpp.hpp \
  $(MOCKCPP_HEADERS_PATH)/mokc.h 

BUILT_SOURCES = $(EXTRA_HEADERS)
CLEANFILES = $(EXTRA_HEADERS)


MOCKCPP_SRCS = \
 AfterMatcher.cpp \
 AnyBase.cpp \
 AnyCast.cpp \
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
 VirtualTableUtils.cpp \
 VirtualTable.cpp \
 ChainableMockMethodContainer.cpp \
 ChainableMockMethodNameKey.cpp \
 ChainableMockMethodIndexKey.cpp \
 StubContainer.cpp \
 StringConstraint.cpp \
 IsStringStartWith.cpp \
 IsStringEndWith.cpp \
 IsStringContains.cpp \
 DelegatedMethodGetter.cpp \
 DieStub.cpp \
 InterfaceInfo.cpp \
 GenericMethodIndicesChecker.cpp \
 DestructorChecker.cpp \
 HookMockObject.cpp \
 CApiHookKey.cpp

libmockcpp_la_SOURCES = $(MOCKCPP_SRCS)

if USE_TEST_TARGET
libmockcpp_for_test_la_SOURCES = $(MOCKCPP_SRCS)
endif

ALLOW_MI = @MOCKCPP_ALLOW_MI@
MAX_INHERITANCE = @MOCKCPP_MI@
MAX_VTBL_SIZE = @MOCKCPP_MVS@
MAX_PARAMETERS = @MOCKCPP_MAX_PARAMS@

DIFF = diff
COPY = cp
RM = rm -f

EXTRA_VTBL_HEADERS_DEFS = --allow-mi=$(ALLOW_MI) --max-inheritance=$(MAX_INHERITANCE) \
                        --max-vtbl-size=$(MAX_VTBL_SIZE) --include-path=$(MOCKCPP_SRC_PATH)

EXTRA_PARAMS_HEADERS_DEFS = --max-parameters=$(MAX_PARAMETERS) --include-path=$(MOCKCPP_SRC_PATH)

$(VBTL_RELATED_HEADER_FILES) : 
	@$(PYTHON) $(top_builddir)/src/generate_vtbl_related_files.py $(EXTRA_VTBL_HEADERS_DEFS) $(@F)
	@$(DIFF) $@ $(@F) >/dev/null 2>&1 || $(COPY) $(MOCKCPP_SRC_PATH)/$(@F) $@
	@$(RM) $(MOCKCPP_SRC_PATH)/$(@F)

$(ARG_RELATED_HEADER_FILES) : 
	@$(PYTHON) $(top_builddir)/src/generate_arg_related_files.py $(EXTRA_PARAMS_HEADERS_DEFS) $(@F)
	@$(DIFF) $@ $(@F) >/dev/null 2>&1 || $(COPY) $(MOCKCPP_SRC_PATH)/$(@F) $@
	@$(RM) $(MOCKCPP_SRC_PATH)/$(@F)

