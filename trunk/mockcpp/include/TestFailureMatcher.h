
#ifndef __MOCKCPP_TEST_FAILURE_MATCHER_H
#define __MOCKCPP_TEST_FAILURE_MATCHER_H

#include <mockcpp.h>
#include <Matcher.h>

MOCKCPP_NS_START

class TestFailureMatcher : public Matcher
{
public:

    TestFailureMatcher(const std::string& msg
                      ,const std::string& str);

    bool matches(const Invocation& inv) const;
    void increaseInvoked(const Invocation& inv);
    std::string toString(void) const;
    void verify(void);

private:
    std::string msg;
    std::string str;
};

MOCKCPP_NS_END

#endif

