
#include <cxxtest/TestSuite.h>

#include <ChainableMockMethodNameKey.h>

class TestChainableMockMethodNameKey: public CxxTest::TestSuite
{
   ChainableMockMethodNameKey* key;

   struct ChainableMockMethodNameKeyStub
    : public ChainableMockMethodKey
   {
      ChainableMockMethodNameKeyStub(const std::string& name)
         : methodName(name)
      {}

      bool equals(const ChainableMockMethodKey * const rhs) const
      { return true; }

      std::string& getMethodName() const
      {
          return const_cast<std::string&>(methodName);
      }

   private:
      std::string methodName;
   };

public:

	void setUp()
   {
      key = new ChainableMockMethodNameKey("method"); 
   }

	void tearDown()
   {
      delete key;
      key = 0;
   }

	/////////////////////////////////////////////////////////
	void testShouldBeAChainableMockMethodKeyType()
	{
      TS_ASSERT(dynamic_cast<ChainableMockMethodNameKey*>(key) != 0);
   }

	/////////////////////////////////////////////////////////
   void testShouldBeAMethodNameGetter()
   {
      TS_ASSERT(dynamic_cast<MethodNameGetter*>(key) != 0);
   }

	/////////////////////////////////////////////////////////
   void testShouldBeEqualToItself()
   {
      TS_ASSERT(key->equals(key));
   }
   
   void testShouldNotEqualToNullPointer()
   {
      TS_ASSERT(!key->equals(0));
   }

   void testShouldNotEqualToOtherTypesOfKeys()
   {
      ChainableMockMethodKey* rhs = new ChainableMockMethodNameKeyStub("method");
      TS_ASSERT(!key->equals(rhs));
      delete rhs;
   }

   void testShouldEqualToSameTypeOfKeysWithSameName()
   {
      ChainableMockMethodKey* rhs = new ChainableMockMethodNameKey("method");
      TS_ASSERT(key->equals(rhs));
      delete rhs;
   }

   void testShouldNotEqualToSameTypeOfKeysWithDifferentName()
   {
      ChainableMockMethodKey* rhs = new ChainableMockMethodNameKey("method1");
      TS_ASSERT(!key->equals(rhs));
      delete rhs;
   }
};

