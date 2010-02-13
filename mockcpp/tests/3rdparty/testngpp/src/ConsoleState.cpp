
#if defined(_MSC_VER)
#include <windows.h>
#endif

#include <testngpp/utils/ConsoleState.h>

TESTNGPP_NS_START

namespace 
{
   #if defined(_MSC_VER)
   void setTextColor(unsigned int color)
   {
      ::SetConsoleTextAttribute
            ( ::GetStdHandle(STD_OUTPUT_HANDLE)
            , color);
   }
   #endif
   ////////////////////////////////////////////////////////
   std::ostream& switchToFail(std::ostream& os, bool colorful)
   {
      if(colorful)
      {
   #ifdef _MSC_VER
         setTextColor( FOREGROUND_RED | FOREGROUND_INTENSITY);
   #else
         os << "\033[1;31m";
   #endif
      }
      return os;
   }
   
   ////////////////////////////////////////////////////////
   std::ostream& switchToSucc(std::ostream& os, bool colorful)
   {
      if(colorful)
      {
   #ifdef _MSC_VER
         setTextColor( FOREGROUND_GREEN | FOREGROUND_INTENSITY);
   #else
         os << "\033[1;32m";
   #endif
      }
      return os;
   } 
   
   ////////////////////////////////////////////////////////
   std::ostream& switchToNorm(std::ostream& os, bool colorful)
   {
      if(colorful)
      {
   #ifdef _MSC_VER
         setTextColor(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
   #else
         os << "\033[0m";
   #endif
      }
      return os;
   }
   
   ////////////////////////////////////////////////////////
   std::ostream& switchToInfo(std::ostream& os, bool colorful)
   {
      if(colorful)
      {
   #ifdef _MSC_VER
         setTextColor(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
   #else
         os << "\33[1;36m";
   #endif
      }
      return os;
   }

   ////////////////////////////////////////////////////////
   std::ostream& switchToWarning(std::ostream& os, bool colorful)
   {
      if(colorful)
      {
   #ifdef _MSC_VER
         setTextColor(FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
   #else
         os << "\33[1;35m";
   #endif
      }
      return os;
   }
}

///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Succ& succ)
{
   return switchToSucc(os, succ.isColorful());
}

///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Fail& fail)
{
   return switchToFail(os, fail.isColorful());
}

///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Normal& norm)
{
   return switchToNorm(os, norm.isColorful());
}

///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Info& info)
{
   return switchToInfo(os, info.isColorful());
}

///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Warning& warn)
{
   return switchToWarning(os, warn.isColorful());
}

///////////////////////////////////////////////////////////
TESTNGPP_NS_END
