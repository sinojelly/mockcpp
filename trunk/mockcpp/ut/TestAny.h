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

#include <limits>

#include <testcpp/testcpp.hpp>
#include <mockcpp/types/Any.h>
#include <mockcpp/types/RefAny.h>
#include <mockcpp/types/AnyCast.h>
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

   void testShouldBeAbleCastUnsignedCharToUnsignedShort()
   {
      Any a((unsigned char)12);

      TS_ASSERT(any_castable<unsigned short>(a));
      TS_ASSERT_EQUALS(12, any_cast<unsigned short>(a));
   }

   void testShouldBeAbleCastNonnegtiveShortToUnsignedShort()
   {
      Any a((short)5);

      TS_ASSERT(any_castable<unsigned short>(a));
      TS_ASSERT_EQUALS(5, any_cast<unsigned short>(a));
   }

   void testShouldBeAbleCastNonnegtiveCharToUnsignedShort()
   {
      Any a((char)2);

      TS_ASSERT(any_castable<unsigned short>(a));
      TS_ASSERT_EQUALS(2, any_cast<unsigned short>(a));
   }

   void testShouldBeAbleCastUnsignedIntWithinLimitationToUnsignedShort()
   {
      Any a(65535);

      TS_ASSERT(any_castable<unsigned short>(a));
      TS_ASSERT_EQUALS(65535, any_cast<unsigned short>(a));
   }

   void testShouldNotCastUnsignedIntExceedingTheLimitationToUnsignedShort()
   {
      Any a(65536);

      TS_ASSERT(!any_castable<unsigned short>(a));
   }

   void testShouldBeAbleCastUnsignedShortToUnsignedInt()
   {
      Any a((unsigned short)15);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(15, any_cast<unsigned int>(a));
   }

   void testShouldBeAbleCastUnsignedCharToUnsignedInt()
   {
      Any a((unsigned char)12);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(12, any_cast<unsigned int>(a));
   }

   void testShouldBeAbleCastNonnegtiveIntToUnsignedInt()
   {
      Any a(1);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(1, any_cast<unsigned int>(a));
   }

   void testShouldBeAbleCastNonnegtiveShortToUnsignedInt()
   {
      Any a((short)5);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(5, any_cast<unsigned int>(a));
   }

   void testShouldBeAbleCastNonnegtiveCharToUnsignedInt()
   {
      Any a((char)2);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(2, any_cast<unsigned int>(a));
   }

   void testShouldBeAbleCastNonnegtiveIntToUnsignedLong()
   {
      Any a(1);

      TS_ASSERT(any_castable<unsigned long>(a));
      TS_ASSERT_EQUALS(1, any_cast<unsigned long>(a));
   }

   void testShouldBeAbleToCastNonnegtiveShortToUnsignedLong()
   {
      Any a((short)5);

      TS_ASSERT(any_castable<unsigned long>(a));
      TS_ASSERT_EQUALS(5, any_cast<unsigned long>(a));
   }

   void testShouldBeAbleToCastNonnegtiveCharToUnsignedLong()
   {
      Any a((char)2);

      TS_ASSERT(any_castable<unsigned long>(a));
      TS_ASSERT_EQUALS(2, any_cast<unsigned long>(a));
   }

   void testShouldBeAbleToCastNonnegtiveIntToUnsignedLong()
   {
      Any a((int)5);

      TS_ASSERT(any_castable<unsigned long>(a));
      TS_ASSERT_EQUALS(5, any_cast<unsigned long>(a));
   }

   void testShouldBeAbleToCastInScopeUnsignedCharToChar()
   {
      Any a((unsigned char)std::numeric_limits<char>::max());

      TS_ASSERT(any_castable<char>(a));
      TS_ASSERT_EQUALS(std::numeric_limits<char>::max(), any_cast<char>(a));
   }

   void testShouldNotCastInScopeUnsignedCharToChar()
   {
      Any a((unsigned char)std::numeric_limits<char>::max()+1);

      TS_ASSERT(!any_castable<char>(a));
   }

   void testShouldBeAbleToCastInScopeUnsignedShortToShort()
   {
      Any a((unsigned short)32767);

      TS_ASSERT(any_castable<short>(a));
      TS_ASSERT_EQUALS(32767, any_cast<short>(a));
   }

   void testShouldNotCastInScopeUnsignedShortToShort()
   {
      Any a((unsigned short)32768);

      TS_ASSERT(!any_castable<short>(a));
   }

   void testShouldBeAbleToCastInScopeUnsignedIntToInt()
   {
      Any a((unsigned int)std::numeric_limits<int>::max());

      TS_ASSERT(any_castable<int>(a));
      TS_ASSERT_EQUALS(std::numeric_limits<int>::max(), any_cast<int>(a));
   }

   void testShouldNotCastInScopeUnsignedIntToInt()
   {
      Any a((unsigned int)std::numeric_limits<int>::max()+1);

      TS_ASSERT(!any_castable<int>(a));
   }

   void testShouldBeAbleToCastInScopeUnsignedLongToLong()
   {
      Any a((unsigned long)std::numeric_limits<long>::max());

      TS_ASSERT(any_castable<long>(a));
      TS_ASSERT_EQUALS(std::numeric_limits<long>::max(), any_cast<long>(a));
   }

   void testShouldNotCastInScopeUnsignedLongToLong()
   {
      Any a((unsigned long)std::numeric_limits<long>::max()+1);

      TS_ASSERT(!any_castable<long>(a));
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

