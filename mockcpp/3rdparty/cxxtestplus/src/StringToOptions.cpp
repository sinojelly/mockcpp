
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <cstring>

#include <testcpp/utils/StringToOptions.h>

TESTCPP_NS_START

namespace
{
   struct ParseState
   {
      enum OptionFlag
      {
         NON,
         START,
         IN,
         END
      };

      int n;
      bool inDoubleQuote ;
      bool isLastCharABlank ;
      OptionFlag flag;

      ParseState()
         : n(0)
         , inDoubleQuote(false)
         , isLastCharABlank(true)
         , flag(NON)
      {}
   };

   #define PREDICT_CHECK(predict) do { \
      if(!(predict)) return false; \
   }while(0)

   ///////////////////////////////////////////////////
   bool scanInDoubleQuote(ParseState& state, char c)
   {
      PREDICT_CHECK(state.inDoubleQuote);

      if(c == '\"')
      {
         state.inDoubleQuote = false;
      }

      state.flag = ParseState::IN;

      return true;
   }

   ///////////////////////////////////////////////////
   bool scanInBlank(ParseState& state, char c)
   {
      PREDICT_CHECK(::isblank(c));

      if(!state.isLastCharABlank)
      {
         ++state.n;
      }

      state.flag = state.isLastCharABlank ? \
         ParseState::NON: ParseState::END;

      return true;
   }

   ///////////////////////////////////////////////////
   bool scanInNonBlank(ParseState& state, char c)
   {
      PREDICT_CHECK(!::isblank(c));

      if(c == '\"')
      {
         state.inDoubleQuote = true;
      }

      state.flag = state.isLastCharABlank ? \
         ParseState::START : ParseState::IN;

      return true;
   }

   ///////////////////////////////////////////////////
   void scan(ParseState& state, char c)
   {
      scanInDoubleQuote(state, c) || scanInBlank(state, c) || scanInNonBlank(state, c);
      state.isLastCharABlank = ::isblank(c);
   }

   char* createArg(char* s, char* e)
   {
      size_t len = e-s;
      char* p = new char[len + 1];
      ::strncpy(p, s, len);
      p[len] = 0;
      return p;
   }

   ///////////////////////////////////////////////////
   char** parseToCArgs(const std::string& s, int argc)
   {
      char** argv = new char*[argc];
      char* p = const_cast<char*>(s.c_str());
      ParseState state;
      char* pArg = 0;

      for(; (*p) != 0; p++)
      {
         scan(state, *p);

         switch(state.flag)
         {
         case ParseState::START:
            pArg = p; break;
         case ParseState::END:
            argv[state.n - 1] = createArg(pArg, p);
            break;
         }
      }

      return argv;
   }
}

int StringToOptions::
getNumberOfArgsInString(const std::string& s)
{
   std::string str = s + " ";
   char* p = const_cast<char*>(str.c_str());
   ParseState state;

   for(; (*p) != 0; p++)
   {
      scan(state, *p);
   }

   return state.n;
}

StringToOptions::CArgs
StringToOptions::parse(const std::string& s)
{
   int argc = getNumberOfArgsInString(s);
   if(argc == 0)
     return CArgs(argc, 0);

   return CArgs(argc, parseToCArgs(s + " ", argc));
}


TESTCPP_NS_END
