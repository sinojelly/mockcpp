
#include <InvocationMocker.h>
#include <ChainableMockMethodCore.h>
#include <Matcher.h>
#include <Stub.h>
#include <Any.h>
#include <Asserter.h>
#include <InvocationId.h>
#include <Method.h>

#include <list>
#include <algorithm>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
class InvocationMockerImpl
{
public:
    typedef std::list<Matcher*>  List;
    typedef List::iterator Iterator;
    typedef List::const_iterator ConstIterator;

	///////////////////////////////////////////////////
    List matchers;
    bool hasBeenInvoked;
    Method* belongedMethod;
    InvocationId* id ;
    Stub* stub;

	///////////////////////////////////////////////////
    InvocationMockerImpl(Method* method)
		: belongedMethod(method), hasBeenInvoked(false), id(0), stub(0)
    {}

    ~InvocationMockerImpl()
    { reset(); }

    bool matches(const Invocation& inv) const;
    void increaseInvoked(const Invocation& inv);
    Any& invoke(const Invocation& inv);

    void reset();
    void verify();
    std::string toString() const;
};

/////////////////////////////////////////////////////////
namespace
{
const std::string normalSpace = "     ";

const std::string& space()
{
	return normalSpace;
}
}

std::string
InvocationMockerImpl::toString() const
{
    std::ostringstream ss;

    ss << "method(" << belongedMethod->getName() << ")";

    for (ConstIterator i = matchers.begin(); i != matchers.end(); ++i)
    {
      ss << "\n" << space() << (*i)->toString();
    }

    if (stub != 0)
    {
      ss << "\n" << space() << stub->toString();
    }

    if(id != 0)
    {
      ss << "\n" << space() << id->toString();
    }
   
    ss << ";";

    return ss.str();
}

/////////////////////////////////////////////////////////
namespace
{
    void verifyMatcher(Matcher* matcher)
    {
      matcher->verify();
    }
}

/////////////////////////////////////////////////////////
void InvocationMockerImpl::verify()
{
    for_each(matchers.begin(), matchers.end(), verifyMatcher);
}

/////////////////////////////////////////////////////////
namespace
{
    void deleteMatcher(Matcher* matcher)
    {
      delete matcher;
    }
}

///////////////////////////////////////////////////////////
void InvocationMockerImpl::reset()
{
    for_each(matchers.begin(), matchers.end(), deleteMatcher);

    matchers.clear();

    if (stub != 0)
    {
      delete stub;
      stub = 0;
    }

    if (id != 0)
    {
      delete id;
      id = 0;
    }
}

///////////////////////////////////////////////////////////
bool
InvocationMockerImpl::matches(const Invocation& inv) const
{
    ConstIterator i = matchers.begin();
    for (; i != matchers.end(); ++i)
    {
      if (!(*i)->matches(inv))
      {
        return false;
      }
    }

    return true;
}

///////////////////////////////////////////////////////////
void
InvocationMockerImpl::increaseInvoked(const Invocation& inv) 
{
    for (Iterator i = matchers.begin(); i != matchers.end(); ++i)
    {
      (*i)->increaseInvoked(inv);
    }
}

///////////////////////////////////////////////////////////
Any&
InvocationMockerImpl::invoke(const Invocation& inv)
{
    increaseInvoked(inv);

    hasBeenInvoked = true;

    if (stub != 0)
    {
      return stub->invoke(inv);
    } 

    return getVoidAny();
}

///////////////////////////////////////////////////////////
InvocationMocker::InvocationMocker(Method* method)
   : This(new InvocationMockerImpl(method))
{
}

///////////////////////////////////////////////////////////
InvocationMocker::~InvocationMocker()
{
    delete This;
}

///////////////////////////////////////////////////////////
Method*
InvocationMocker::getMethod() const
{
    return This->belongedMethod;
}

///////////////////////////////////////////////////////////
void InvocationMocker::setId(InvocationId* id)
{
    if (This->id != 0) delete This->id;

    This->id = id;
}

///////////////////////////////////////////////////////////
void InvocationMocker::addMatcher(Matcher* matcher)
{
    This->matchers.push_back(matcher);
}

///////////////////////////////////////////////////////////
bool InvocationMocker::hasBeenInvoked(void) const
{
    return This->hasBeenInvoked;
}

///////////////////////////////////////////////////////////
void InvocationMocker::setStub(Stub* stub) 
{
    This->stub = stub;
}

///////////////////////////////////////////////////////////
const InvocationId* const InvocationMocker::getId(void) const
{
    return This->id;
}

///////////////////////////////////////////////////////////
bool InvocationMocker::matches(const Invocation& inv) const
{
    return This->matches(inv);
}

///////////////////////////////////////////////////////////
std::string InvocationMocker::toString() const
{
    return This->toString();
}

///////////////////////////////////////////////////////////
Any& InvocationMocker::invoke(const Invocation& inv)
{
    try
    {
      return This->invoke(inv);
    }
    catch (Exception& ex)
    {
      MOCKCPP_FAIL(ex.getMessage() + "\n" +
                    This->toString());
    }

	return getEmptyAny();
}

///////////////////////////////////////////////////////////
void InvocationMocker::verify()
{
    try
    {
      This->verify();
    }
    catch (Exception& ex)
    {
      MOCKCPP_FAIL(ex.getMessage() + "\n" +
                    This->toString());
    }
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

