
#ifndef __TESTNGPP_CONSOLE_STATE_H
#define __TESTNGPP_CONSOLE_STATE_H

#include <ostream>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct ConsoleState
{
protected:
   ConsoleState(bool c)
      : colorful(c)
   {}
      
public:
   bool isColorful() const
   {
      return colorful;
   }
      
private:
      bool colorful;
};
   
////////////////////////////////////////////////////////
struct Succ : public ConsoleState
{
   Succ(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
struct Fail : public ConsoleState
{
   Fail(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
struct Normal : public ConsoleState
{
   Normal(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
struct Info : public ConsoleState
{
   Info(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
struct Warning : public ConsoleState
{
   Warning(bool colorful) : ConsoleState(colorful)
   {}
};

////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Succ& succ);
std::ostream& operator<<(std::ostream& os, const Fail& fail);
std::ostream& operator<<(std::ostream& os, const Normal& norm);
std::ostream& operator<<(std::ostream& os, const Info& info);
std::ostream& operator<<(std::ostream& os, const Warning& warn);

////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

