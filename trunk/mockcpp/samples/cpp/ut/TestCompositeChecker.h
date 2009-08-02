

// For CxxTest
#include <cxxtest/TestSuite.h>

// For Mock
#include <mockcpp.hpp>

// For Tested Class
#include <CompositeChecker.h>

using namespace mockcpp;

using namespace cpp;

class TestCompositeChecker : public CxxTest::TestSuite
{
public:
   CompositeChecker::List checkers;

   MockObject<Checker> checker0;
   MockObject<Checker> checker1;
   MockObject<Checker> checker2;

	void setUp()
   {
       checkers.push_back(checker0);
       checkers.push_back(checker1);
       checkers.push_back(checker2);
   }

	void tearDown()
   {
      checkers.clear();

      checker0.reset();
      checker1.reset();
      checker2.reset();
   }

	/////////////////////////////////////////////////////////

	void testShouldInvokeCheckersInOrder()
	{
       std::string user("darwin");

       checker0.method(&Checker::check)
               .expects(atLeast(1))
               .with(eq(user))
               .will(returnValue(true))
               .id("0");

       checker1.method(&Checker::check)
               .expects(atLeast(1))
               .with(eq(user))
               .after(checker0, "0")
               .will(returnValue(true))
               .id("1");

       checker2.method(&Checker::check)
               .expects(atLeast(1))
               .with(eq(user))
               .after(checker1, "1")
               .will(returnValue(true));

       ///////////////////////////////////////////////
       CompositeChecker compositeChecker(&checkers);

       compositeChecker.check(user);

       ///////////////////////////////////////////////
		 checker0.verify();
		 checker1.verify();
		 checker2.verify();
	}
};

