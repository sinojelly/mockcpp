
#include <cxxtest/TestSuite.h>

#include <StringConstraint.h>

#include <StringPredict.h>

USING_MOCKCPP_NS

class TestStringConstraint: public CxxTest::TestSuite
{
   struct StringPredictStub : public StringPredict
   {

     bool predict(const std::string& input, const std::string& target) const 
     {
        return input == target;
     }

     std::string toString(const std::string& target) const 
     {
         return std::string("<") + target + std::string(">");
     }
   };

private:

   MemoryCheckPoint checkpoint;
   StringConstraint* constraint;
   
public:
   void setUp()
   {
      checkpoint = mockcppSetCheckPoint();

      constraint = new StringConstraint("abcd", new StringPredictStub());
   }

   void tearDown()
   {
      delete constraint;

      MOCKCPP_CHECK_POINT_VERIFY(checkpoint);
   }

   void testShouldBeAbleToEvalAStringWithSpecifiedPredict()
   {
      std::string input0("abcd");
      TS_ASSERT(constraint->eval(input0));

      std::string input1("aabcd");
      TS_ASSERT(!constraint->eval(input1));
   }

   void testShouldBeAbleToEvalAPCharWithSpecifiedPredict()
   {
      char* input = "abcd";
      TS_ASSERT(constraint->eval(input));
   }

   void testShouldBeAbleToEvalAPConstCharWithSpecifiedPredict()
   {
      const char* input = "abcd";
      TS_ASSERT(constraint->eval(input));
   }

   void testShouldBeAbleToEvalAPUCharWithSpecifiedPredict()
   {
      unsigned char* input = (unsigned char*)"abcd";
      TS_ASSERT(constraint->eval(input));
   }

   void testShouldBeAbleToEvalAPConstUCharWithSpecifiedPredict()
   {
      const unsigned char* input = (const unsigned char*)"abcd";
      TS_ASSERT(constraint->eval(input));
   }

   void testShouldBeAbleToEvalANullPCharWithSpecifiedPredict()
   {
      char* input = 0;
      TS_ASSERT(!constraint->eval(input));
   }
};
