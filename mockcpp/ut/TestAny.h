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

#include <testcpp/testcpp.hpp>
#include <mockcpp/types/Any.h>
#include <mockcpp/types/RefAny.h>
#include <mockcpp/IsRef.h>

USING_MOCKCPP_NS
          
class TestAny: public TESTCPP_NS::TestFixture 
{

public:
	void setUp()
	{
	}

	void tearDown()
	{
	}

	/////////////////////////////////////////////////////////

	void testShouldBeEmptyIfANewInstanceIsNotInitialized()
	{
		Any i;

		TS_ASSERT(i.empty());
	}

	void testShouldNotBeEmptyIfAInstanceIsInitialized()
	{
		Any i(0);

		TS_ASSERT(!i.empty());
	}

	void testShouldBeCastableForSameType()
	{
		RefAny ref(10);

		TS_ASSERT(any_castable<int>(ref));
	}

   void testShouldBeAbleStorePChar()
   {
		RefAny ref((char*)"abcd");

		TS_ASSERT(any_castable<char*>(ref));
   }
   
   void testShouldBeAbleStoreNullPchar()
   {
		RefAny ref((char*)0);

		TS_ASSERT(any_castable<char*>(ref));
   }

   void testShouldBeAbleToGetTypeAndValueString()
   {
      const std::string& str = std::string("abcdef");
      RefAny ref(str);

      TS_ASSERT_EQUALS(std::string("\"") + str + std::string("\""), ref.toString());
   }

   void testShouldBeAbleToAnyCastReferenceCorrectly()
   {
      const std::string& str = std::string("abcdef");
      Any i(str);
      Any& ref = i;

      const std::string& result = any_cast<const std::string&>(ref);
      TS_ASSERT_EQUALS(std::string("abcdef"), result);
   }
};

