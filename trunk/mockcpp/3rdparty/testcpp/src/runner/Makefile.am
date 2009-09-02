
AM_CPPFLAGS = \
  -I$(top_builddir)/include \
  $(LTDLINCL)

lib_LTLIBRARIES = libtestcpprunner.la 

nodist_libtestcpprunner_la_SOURCES = \
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

bin_PROGRAMS = testcpp-runner

testcpp_runner_LDADD = \
  $(top_builddir)/src/runner/libtestcpprunner.la \
  $(top_builddir)/src/libtestcpp.la \
  $(LIBLTDL)

testcpp_runner_LDFLAGS = -export-dynamic

testcpp_runner_SOURCES = \
  TestRunnerMain.cpp

TestFoo.cpp : TestFoo.h
	@$(PYTHON) $(top_builddir)/testcppgen.py -o $@ $<
