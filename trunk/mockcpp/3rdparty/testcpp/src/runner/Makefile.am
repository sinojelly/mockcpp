
AM_CPPFLAGS = \
  -I$(top_builddir)/include \
  $(LTDLINCL)

noinst_LTLIBRARIES = libtestcpprunner.la 

libtestcpprunner_la_LDFLAGS = \
  -export-dynamic \
  -rpath /dev/null \
  -no-undefined \
  $(top_builddir)/src/libtestcpp.la \
  $(LIBLTDL)

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

noinst_PROGRAMS = testcpp-runner

testcpp_runner_LDADD = \
  $(top_builddir)/src/runner/libtestcpprunner.la 

testcpp_runner_LDFLAGS = -export-dynamic

testcpp_runner_SOURCES = \
  TestRunnerMain.cpp

TestFoo.cpp : TestFoo.h
	@$(PYTHON) $(top_builddir)/testcppgen.py -o $@ $<
