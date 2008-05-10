
#include <TypelessMatcherAdapter.h>
#include <TypelessMatcher.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////
struct TypelessMatcherAdapterImpl
{
    TypelessMatcher* matcher;
    bool selfManaged;

    TypelessMatcherAdapterImpl(TypelessMatcher* m, bool sm)
		: matcher(m), selfManaged(sm)
    {}

    ~TypelessMatcherAdapterImpl()
    {
      if(selfManaged) {
        delete matcher;
      }
    }
};

/////////////////////////////////////////////////////////////
TypelessMatcherAdapter::TypelessMatcherAdapter(
             TypelessMatcher* tm
           , bool selfManaged)
    : This(new TypelessMatcherAdapterImpl(tm, selfManaged))
{
}
/////////////////////////////////////////////////////////////
TypelessMatcherAdapter::~TypelessMatcherAdapter()
{
    delete This;
}
/////////////////////////////////////////////////////////////
bool TypelessMatcherAdapter::matches(const Invocation& inv) const
{
    return This->matcher->matches();
}
/////////////////////////////////////////////////////////////
void TypelessMatcherAdapter::increaseInvoked(const Invocation& inv) 
{
    return This->matcher->increaseInvoked();
}

/////////////////////////////////////////////////////////////
void TypelessMatcherAdapter::verify() 
{
    return This->matcher->verify();
}

std::string TypelessMatcherAdapter::toString() const
{
	return This->matcher->toString();
}
/////////////////////////////////////////////////////////////

MOCKCPP_NS_END

