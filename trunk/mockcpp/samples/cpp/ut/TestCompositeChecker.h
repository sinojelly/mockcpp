
/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

// for testcpp
#include <testcpp/testcpp.hpp>

// For Mock
#include <mockcpp/mockcpp.hpp>

// For Tested Class
#include <CompositeChecker.h>


USING_MOCKCPP_NS

using namespace cpp;

class TestCompositeChecker: public TESTCPP_NS::TestFixture
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

       MOCK_METHOD(checker0, check)
            .expects(atLeast(1))
            .with(eq(user))
            .will(returnValue(true))
            .id("0");

       MOCK_METHOD(checker1, check)
            .expects(atLeast(1))
            .with(eq(user))
            .after(checker0, "0")
            .will(returnValue(true))
            .id("1");

       MOCK_METHOD(checker2, check)
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

