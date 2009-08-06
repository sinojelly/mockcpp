
#include <RepeatStub.h>
#include <Asserter.h>
#include <OutputStringStream.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
RepeatStub::RepeatStub(const Any& value, unsigned int times)
		: returnValue(value), repeatTimes(times), repeatedTimes(0)
{}

/////////////////////////////////////////////////////
bool RepeatStub::isCompleted() const
{
   return repeatedTimes >= repeatTimes;
}

/////////////////////////////////////////////////////
Any& RepeatStub::invoke(void)
{
    oss_t oss;

    oss << "The repeat times ("
        << repeatTimes 
        << ") you specified has been reached";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
       oss.str(),
       repeatedTimes < repeatTimes); 

    repeatedTimes++;

    return returnValue;
}

/////////////////////////////////////////////////////
const std::type_info& RepeatStub::type() const
{
    return returnValue.type();
}

/////////////////////////////////////////////////////
std::string RepeatStub::toString(void) const
{
    oss_t oss;

    oss << "repeat(" << returnValue.toTypeAndValueString() 
        << ", " << repeatTimes << ")";

    return oss.str();
}

MOCKCPP_NS_END

