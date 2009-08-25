
AM_CPPFLAGS = -I$(top_builddir)/include $(INCLTDL)

noinst_LTLIBRARIES = libtestcpprunner.la 

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
  TestFixtureSandboxRunnerFactory.cpp \
  LTTestListenerLoader.cpp \
  FixtureNameOnlyTestFilter.cpp \
  CaseNameOnlyTestFilter.cpp \
  SpecifiedTestFilter.cpp \
  WildcardTestFilter.cpp \
  TestFilterFactory.cpp \
  OptionList.cpp \
  TestRunner.cpp

noinst_PROGRAMS = testcpp-runner

testcpp_runner_LDADD = \
  -L$(top_builddir)/src/runner -ltestcpprunner \
  -L$(top_builddir)/src -ltestcpp $(LIBLTDL)

testcpp_runner_LDFLAGS = \
  -static \
  -export-dynamic

testcpp_runner_SOURCES = \
  TestRunnerMain.cpp

TestFoo.cpp : TestFoo.h
	@$(PYTHON) $(top_builddir)/testcppgen.py -o $@ $<
