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


#include <mockcpp/ChainableMockMethodContainer.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/InvocationMockBuilderGetter.h>


class TestChainableMockMethodContainer : public TESTCPP_NS::TestFixture
{
   struct InvocationMockerNamespaceStub : public InvocationMockerNamespace
   {
      InvocationMockerNamespaceStub()
			: name("InvocationMockerNamespaceStub")
      {}

      InvocationMocker* getInvocationMocker(const std::string& id)  const
      {
         return 0;
      }

      std::string& getName(void) const
      {
          return const_cast<std::string&>(name);
      } 

      std::string name;
   };

private:

    MOCKCPP_NS::ChainableMockMethodNameKey* key;
    InvocationMockerNamespaceStub ns;
    ChainableMockMethodCore* method;

private:

   TESTCPP_RCP checkpoint;

public:

	void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();

      key = new ChainableMockMethodNameKey("method");
		method = new ChainableMockMethodCore("method", &ns);

   }

	void tearDown()
   {
      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

	/////////////////////////////////////////////////////////

	void testShouldBeAbleToAddAMethod()
	{
      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);
      TS_ASSERT_EQUALS(method, container.getMethod(key));
	}

   void testShouldReturnNullIfMethodWithTheSpecifiedKeyWasNotAddedToContainer()
   {
      MOCKCPP_NS::ChainableMockMethodContainer container;
      TS_ASSERT(0 == container.getMethod(key));

      delete key;
		delete method;
   }

   void testShouldThrowExceptionIfAMethodWithTheSameKeyHasBeedAdded()
   {
      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT_THROWS(container.addMethod(key, method), MOCKCPP_NS::Exception);
   }

   void testYouCannotGetTheMethodAnyLongerAfterTheContainerIsReset()
   {
      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);
      container.reset();
      TS_ASSERT(0 == container.getMethod(key));
   }

   void testShouldBeAbleToVerifyEveryMethodInTheContainer()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once());

      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT_THROWS(container.verify(), MOCKCPP_NS::Exception);
   }
  
   void testShouldBeAbleToGetInvocationMockerById()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once()).id("1");

      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT(container.findInvocationMocker("1") != 0);
   }
   
   void testShouldReturnNullIfAInvocationMockerWithSpecifiedIdWasNeverBuilt()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once()).id("1");

      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT(container.findInvocationMocker("0") == 0);
   }
};

