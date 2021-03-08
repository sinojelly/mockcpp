
#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngpp/ExceptionKeywords.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestExceptionKeywords: public CxxTest::TestSuite
{
   struct Fail0 {};
   struct Fail1 {};

public:

   ///////////////////////////////////////////////////
   int proc0()
   {
      int value = 100;

      __TESTNGPP_TRY
      {
         value = 101;
         throw Fail0();
      }
      __TESTNGPP_CATCH(Fail0&)
      {
         value = 102;
      }
      __TESTNGPP_FINALLY
      {
         value = 103;
      }
      __TESTNGPP_DONE

      return value;
   }

   void testShouldExecStmtsInFinallyClauseIfAnExceptionWasThrownInTryClause()
   {
      TS_ASSERT_EQUALS(103, proc0());
   }

   ///////////////////////////////////////////////////
   void proc1(int* value)
   {
      __TESTNGPP_TRY
      {
         *value = 101;
         throw Fail0();
      }
      __TESTNGPP_CATCH(Fail0&)
      {
         *value = 102;
         throw;
      }
      __TESTNGPP_FINALLY
      {
         *value = 103;
      }
      __TESTNGPP_DONE
   }

   void testShouldExecStmtsInFinallyClauseIfAnExceptionWasThrownInCatchClause()
   {
      int value = 0;

      TS_ASSERT_THROWS(proc1(&value), Fail0);
      TS_ASSERT_EQUALS(103, value);
   }

   ///////////////////////////////////////////////////
   int proc2()
   {
      int value = 100;

      __TESTNGPP_TRY
      {
         value = 101;
      }
      __TESTNGPP_CATCH(Fail0&)
      {
         value = 102;
         throw;
      }
      __TESTNGPP_FINALLY
      {
         value = 103;
      }
      __TESTNGPP_DONE

      return value;
   }

   void testShouldExecStmtsInFinallyClauseIfNoExceptionWasThrown()
   {
      TS_ASSERT_EQUALS(103, proc2());
   }

   ///////////////////////////////////////////////////

   void proc3(int* value)
   {
      __TESTNGPP_DO
      {
         *value = 101;
         throw Fail0();
      }
      __TESTNGPP_CLEANUP
      {
         *value = 103;
      }
      __TESTNGPP_DONE
   }

   void testShouldExecStmtsInCleanupClauseIfAnExceptionWasThrownInTryClauseAndNoCatch()
   {
      int value = 0;

      TS_ASSERT_THROWS(proc3(&value), Fail0);
      TS_ASSERT_EQUALS(103, value);
   }

   ///////////////////////////////////////////////////
   void proc4(int* value)
   {
      __TESTNGPP_TRY
      {
         *value = 101;
         throw Fail0();
      }
      __TESTNGPP_CATCH(...)
      {
         *value = 102;
         throw;
      }
      __TESTNGPP_FINALLY
      {
         *value = 103;
      }
      __TESTNGPP_DONE
   }

   void testShouldExecStmtsInFinallyClauseIfAnExceptionWasThrownInCatchAllClause()
   {
      int value = 0;

      TS_ASSERT_THROWS(proc4(&value), Fail0);
      TS_ASSERT_EQUALS(103, value);
   }

   ///////////////////////////////////////////////////
   void proc5(int* value)
   {
      __TESTNGPP_TRY
      {
         *value = 100;
         throw Fail0();
      }
      __TESTNGPP_CATCH(Fail0&)
      {
         *value = 101;
         throw Fail0();
      }
      __TESTNGPP_CATCH(...)
      {
         *value = 102;
         throw;
      }
      __TESTNGPP_FINALLY
      {
         *value = 103;
      }
      __TESTNGPP_DONE
   }

   void testShouldExecStmtsInFinallyClauseIfAnExceptionWasThrownInMoreThanOneCatchClause()
   {
      int value = 0;

      TS_ASSERT_THROWS(proc5(&value), Fail0);
      TS_ASSERT_EQUALS(103, value);
   }

   ///////////////////////////////////////////////////
   int proc6()
   {
      int value = 100;

      __TESTNGPP_TRY
      {
         value = 101;
         throw Fail0();
      }
      __TESTNGPP_CATCH(Fail0&)
      {
         value = 102;
      }
      __TESTNGPP_END_TRY

      return value;
   }

   void testShouldExecStmtsInCatchClauseIfAnExceptionWasThrown()
   {
      TS_ASSERT_EQUALS(102, proc6());
   }

   ///////////////////////////////////////////////////
   int proc7()
   {
      int value = 100;

      __TESTNGPP_TRY
      {
         value = 101;
         throw Fail1();
      }
      __TESTNGPP_CATCH(Fail0&)
      {
         value = 102;
      }
      __TESTNGPP_CATCH(Fail1&)
      {
         value = 103;
      }
      __TESTNGPP_CATCH(...)
      {
         value = 104;
      }
      __TESTNGPP_END_TRY

      return value;
   }

   void testShouldExecStmtsInCatchClauseIfAnExceptionWasThrownAndThereAreMoreThan1CatchClauses()
   {
      TS_ASSERT_EQUALS(103, proc7());
   }
   ///////////////////////////////////////////////////
   int proc8()
   {
      int value = 100;

      __TESTNGPP_TRY
      {
         value = 101;
      }
      __TESTNGPP_CATCH(Fail0&)
      {
         value = 102;
      }
      __TESTNGPP_CATCH(Fail1&)
      {
         value = 103;
      }
      __TESTNGPP_CATCH_ALL
      {
         value = 104;
      }
      __TESTNGPP_END_TRY

      return value;
   }

   void testShouldNotExecStmtsInCatchClauseIfThereIsCatchAnyPresents()
   {
      TS_ASSERT_EQUALS(101, proc8());
   }

};
