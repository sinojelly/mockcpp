
#include <InvocationMocker.h>
#include <ChainableMockMethodCore.h>
#include <Matcher.h>
#include <Stub.h>
#include <Any.h>
#include <Asserter.h>
#include <InvocationId.h>

#include <list>
#include <algorithm>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
struct InvocationMockerImpl
{
    typedef std::list<Matcher*>  List;
    typedef List::iterator Iterator;
    typedef List::const_iterator ConstIterator;

	///////////////////////////////////////////////////
    List matchers;
    bool isInvoked;
    ChainableMockMethodCore* coreMocker;
    InvocationId* id ;
    Stub* stub;

	///////////////////////////////////////////////////
    InvocationMockerImpl(ChainableMockMethodCore* core)
		: coreMocker(core), isInvoked(false), id(0), stub(0)
	 {}

    ~InvocationMockerImpl()
    { reset(); }

    bool matches(const Invocation& inv) const;
    void increaseInvoked(const Invocation& inv);
    Any& invoke(const Invocation& inv);

	 void reset();
    void verify();
    std::string toString(bool wide = false) const;
};

/////////////////////////////////////////////////////////
namespace
{
const std::string wideSpace = "            ";
const std::string normalSpace = "     ";

const std::string& space(bool wide)
{
   return wide ? wideSpace : normalSpace; 
}
}

std::string
InvocationMockerImpl::toString(bool wide) const
{
	std::ostringstream ss;

   ss << coreMocker->getNamespace()->getName()
      << "::method(" << coreMocker->getName() <<  ") \n";

	for(ConstIterator i = matchers.begin(); i != matchers.end(); ++i) {
      ss << space(wide) << (*i)->toString() << "\n";
	}

   if(stub != 0) {
      ss << space(wide) << stub->toString();
   }

   if(id != 0) {
      ss << space(wide) << id->toString();
   }
   
   ss << ";";

	return ss.str();
}
/////////////////////////////////////////////////////////
namespace {
void verifyMatcher(Matcher* matcher)
{
    matcher->verify();
}}
/////////////////////////////////////////////////////////
void InvocationMockerImpl::verify()
{
    for_each(matchers.begin(), matchers.end(), verifyMatcher);
}
/////////////////////////////////////////////////////////
namespace {
void deleteMatcher(Matcher* matcher)
{
    delete matcher;
}}

///////////////////////////////////////////////////////////
void InvocationMockerImpl::reset()
{
    for_each(matchers.begin(), matchers.end(), deleteMatcher);
	 matchers.clear();
    if(stub != 0) {
      delete stub;
      stub = 0;
    }
    if(id != 0) {
      delete id;
      id = 0;
    }
}
///////////////////////////////////////////////////////////
bool
InvocationMockerImpl::matches(const Invocation& inv) const
{
    ConstIterator i = matchers.begin();
    for(; i != matchers.end(); ++i) {
      if(!(*i)->matches(inv)) {
        return false;
      }
    }

    return true;
}
///////////////////////////////////////////////////////////
void
InvocationMockerImpl::increaseInvoked(const Invocation& inv) 
{
    for(Iterator i = matchers.begin(); i != matchers.end(); ++i) {
       (*i)->increaseInvoked(inv);
    }
}
///////////////////////////////////////////////////////////
Any&
InvocationMockerImpl::invoke(const Invocation& inv)
{
    increaseInvoked(inv);

    isInvoked = true;

    if(stub != 0) {
      return stub->invoke(inv);
    } 

    return getEmptyAny();
}

///////////////////////////////////////////////////////////
InvocationMocker::InvocationMocker(ChainableMockMethodCore* core)
   : This(new InvocationMockerImpl(core))
{
}

///////////////////////////////////////////////////////////
InvocationMocker::~InvocationMocker()
{
    delete This;
}

///////////////////////////////////////////////////////////
ChainableMockMethodCore*
InvocationMocker::getMethod() const
{
    return This->coreMocker;
}
///////////////////////////////////////////////////////////
void InvocationMocker::setId(InvocationId* id)
{
    if(This->id != 0) delete This->id;

    This->id = id;
}
///////////////////////////////////////////////////////////
void InvocationMocker::addMatcher(Matcher* matcher)
{
    This->matchers.push_back(matcher);
}
///////////////////////////////////////////////////////////
bool InvocationMocker::isInvoked(void) const
{
    return This->isInvoked;
}
///////////////////////////////////////////////////////////
void InvocationMocker::setStub(Stub* stub) 
{
    This->stub = stub;
}
///////////////////////////////////////////////////////////
const InvocationId* const
InvocationMocker::getId(void) const
{
    return This->id;
}
///////////////////////////////////////////////////////////
bool
InvocationMocker::matches(const Invocation& inv) const
{
    return This->matches(inv);
}

///////////////////////////////////////////////////////////
std::string
InvocationMocker::toString(bool wide) const
{
    return This->toString(wide);
}

///////////////////////////////////////////////////////////
Any&
InvocationMocker::invoke(const Invocation& inv)
{
    try {
      return This->invoke(inv);
    }
    catch(Exception& ex) {
       MOCKCPP_FAIL(ex.getMessage() + "\n" +
                    This->toString(false));
    }
}
///////////////////////////////////////////////////////////
void
InvocationMocker::verify()
{
    try {
		 This->verify();
    }
    catch(Exception& ex) {
       MOCKCPP_FAIL(ex.getMessage() + "\n" +
                    This->toString(false));
    }
}
///////////////////////////////////////////////////////////

MOCKCPP_NS_END

