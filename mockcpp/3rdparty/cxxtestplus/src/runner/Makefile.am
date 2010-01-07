
AM_CPPFLAGS = \
  -I$(top_builddir)/include \
  $(LTDLINCL)

lib_LTLIBRARIES = libcxxtestplusrunner.la 

libcxxtestplusrunner_la_LDFLAGS = \
  -no-undefined \
  $(top_builddir)/src/libcxxtestplus.la \
  $(LIBLTDL)

nodist_libcxxtestplusrunner_la_SOURCES = \
  TestSuiteRunner.cpp \
  TestCaseSandboxResultReporter.cpp \
  TestCaseSandboxResultDecoder.cpp \
  SimpleTestCaseRunner.cpp \
  Sandbox.cpp \
  SandboxProcessor.cpp \
  TestCaseSandboxHandler.cpp \
  TestCaseSandbox.cpp \
  PipeReadableChannel.cpp \
  PipeWrittableChannel.cpp  \
  TestFixtureSandboxRunner.cpp \
  TestFixtureRunnerWrapper.cpp \
  LTTestSuiteLoader.cpp \
  SimpleTestResultDispatcher.cpp \
  SimpleTestResultReporter.cpp \
  SimpleTestCaseResultReporter.cpp \
  SimpleTestSuiteResultReporter.cpp \
  TestFixtureRunnerFactory.cpp \
  SimpleTestFixtureRunner.cpp \
  LTTestListenerLoader.cpp \
  WildcardTestFilter.cpp \
  OrCompositeTestFilter.cpp \
  GeneralTestFilter.cpp \
  TestFilterFactory.cpp \
  PosixFNMatcher.cpp \
  TestRunner.cpp

bin_PROGRAMS = cxxtestplus-runner

cxxtestplus_runner_LDADD = \
  $(top_builddir)/src/runner/libcxxtestplusrunner.la 

cxxtestplus_runner_LDFLAGS = \
  -export-dynamic

cxxtestplus_runner_SOURCES = \
  TestRunnerMain.cpp
