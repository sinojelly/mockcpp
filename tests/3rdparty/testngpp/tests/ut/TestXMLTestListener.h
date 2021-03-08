#include <listeners/XMLTestListener.h>

#include <testngpp/internal/TestSuiteInfoReader.h>
#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/AssertionFailure.h>

#include <testngpp/listener/TestSuiteResultReporter.h>
#include <testngpp/listener/TestCaseResultReporter.h>

#include <mockcpp/mockcpp.hpp>

#include <cxxtest/TestSuite.h>
#include <string>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestXMLTestListener: public CxxTest::TestSuite
{
private:
	XMLTestListener* listener;
	MockObject<TestSuiteInfoReader> testSuiteInfoReader;
	MockObject<TestFixtureInfoReader> testFixtureInfoReader;
	MockObject<TestCaseInfoReader> testCaseInfoReader;
	MockObject<TestSuiteResultReporter> testSuiteResultReporter;
	MockObject<TestCaseResultReporter> testCaseResultReporter;
	std::stringstream* os;

public:

	void setUp() {
		os = new std::stringstream;
		listener = new XMLTestListener(NULL, testSuiteResultReporter, testCaseResultReporter, *os);
	}

	void tearDown() {
		delete listener;
		delete os;
		
		testSuiteInfoReader.verify();
		testFixtureInfoReader.verify();
		testCaseInfoReader.verify();
		testSuiteResultReporter.verify();
		testCaseResultReporter.verify();
	}

	void testXMLTestListener(void) {
		#if 0
		//def __GNUC__
		// TODO: there is a 15 bytes mem leak on linux, but it runs ok on windows. the reason is unknown.
		//STOP_MEM_CHECKER();
		extern void pauseCheckStatus();
		pauseCheckStatus();		
		#endif
		testSuiteInfoReader
			.METHOD(TestSuiteInfoReader::getName)
			.stubs()
			.will(returnValue(std::string("Suite 1")));

		testSuiteResultReporter
			.METHOD(TestSuiteResultReporter::getNumberOfCrashedTestCases)
			.stubs()
			.with(eq((TestSuiteInfoReader*) testSuiteInfoReader))
			.will(returnValue(11));

		testSuiteResultReporter
			.METHOD(TestSuiteResultReporter::getNumberOfFixtures)
			.stubs()
			.with(eq((TestSuiteInfoReader*) testSuiteInfoReader))
			.will(returnValue(6));

      testSuiteResultReporter
			.METHOD(TestSuiteResultReporter::getNumberOfSkippedTestCases)
         .stubs()
         .will(returnValue((unsigned int)2));

      testSuiteResultReporter
			.METHOD(TestSuiteResultReporter::getNumberOfTestCases)
         .stubs()
         .will(returnValue((unsigned int)66));

		testSuiteResultReporter
			.METHOD(TestSuiteResultReporter::getNumberOfErrorTestCases)
			.stubs()
			.with(eq((TestSuiteInfoReader*) testSuiteInfoReader))
			.will(returnValue(22));
		testSuiteResultReporter
			.METHOD(TestSuiteResultReporter::getNumberOfFailedTestCases)
			.stubs()
			.with(eq((TestSuiteInfoReader*) testSuiteInfoReader))
			.will(returnValue(33));

		testCaseInfoReader
			.METHOD(TestCaseInfoReader::getName)
			.stubs()
			.will(returnValue(std::string("Test 1")))
			.then(returnValue(std::string("Test 2")));
		testCaseInfoReader
			.METHOD(TestCaseInfoReader::getNameOfFixture)
			.stubs()
			.will(returnValue(std::string("Fixture 1")))
			.then(returnValue(std::string("Fixture 2")));
		testCaseInfoReader
			.METHOD(TestCaseInfoReader::getFileName)
			.stubs()
			.will(returnValue(std::string("Test-1.cpp")))
			.then(returnValue(std::string("Test-2.cpp")));

		testCaseResultReporter
			.METHOD(TestCaseResultReporter::getTestCaseResult)
			.stubs()
			.with(eq((TestCaseInfoReader*) testCaseInfoReader))
			.will(returnValue((unsigned int) TestCaseResultReporter::TR_SUCCESS))
			.then(returnValue((unsigned int) TestCaseResultReporter::TR_FAILED));

		AssertionFailure assertionFailure((const std::string) "Test-2.cpp",
				1,
				(const std::string) "Unknown");

		listener->startTest();
		listener->startTestSuite(testSuiteInfoReader);
		listener->startTestFixture(testFixtureInfoReader);
		listener->startTestCase(testCaseInfoReader);
		listener->endTestCase(testCaseInfoReader,0,0);
		listener->startTestCase(testCaseInfoReader);
		listener->addCaseFailure(testCaseInfoReader, assertionFailure);
		listener->endTestFixture(testFixtureInfoReader);
		listener->endTestSuite(testSuiteInfoReader);
		listener->endTest(0,0);

		std::string expected =
"<?xml version=\"1.0\"?>\n\
<testsuites>\n\
  <testsuite name=\"Suite 1\" tests=\"66\" fixtures=\"6\" crashes=\"11\" skips=\"2\" errors=\"22\" failures=\"33\">\n\
    <testcase name=\"Test 1\" fixture=\"Fixture 1\" time=\"0\" filename=\"Test-1.cpp\">\n\
    </testcase>\n\
    <testcase name=\"Test 2\" fixture=\"Fixture 2\" time=\"0\" filename=\"Test-2.cpp\">\n\
      <failure>Unknown</failure>\n\
    </testcase>\n\
  </testsuite>\n\
</testsuites>\n";

		TS_ASSERT_EQUALS(expected, os->str());
	}
};
