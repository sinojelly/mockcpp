
#ifndef __MOCKCPP_FUNCTOR_H
#define __MOCKCPP_FUNCTOR_H

#include <mockcpp.h>

#include <string>

#include <GlobalMockObject.h>

MOCKCPP_NS_START

/////////////////////////////////////////////
class BaseFunctor
{
public:
	BaseFunctor(const std::string& fName)
		: name(fName) {}

	std::string getName() const
	{
		return name;
	}

private:
	std::string name;
};

////////////////////////////////////////////
template <typename F>
struct Functor;

////////////////////////////////////////////
template <typename RT>
struct Functor<RT()> : public BaseFunctor
{
    Functor(const std::string& fName)
      : BaseFunctor(fName)
    {}

    RT operator()()
    {
      return GlobalMockObject::instance.invoke<RT>(getName())();
    }
};

////////////////////////////////////////////
template <typename RT, typename P1>
struct Functor<RT(P1)> : public BaseFunctor
{
    Functor(const std::string& name)
      : BaseFunctor(name)
    {}

    RT operator()(P1 p1)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())(p1);
    }
};


////////////////////////////////////////////
template <typename RT, typename P1, typename P2>
struct Functor<RT(P1,P2)> : public BaseFunctor
{
    Functor(const std::string& name)
      : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())(p1, p2);
    }
};

////////////////////////////////////////////
template <typename RT, typename P1, typename P2, typename P3>
struct Functor<RT(P1, P2, P3)> : public BaseFunctor
{
    Functor(const std::string& name)
      : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())(p1, p2, p3);
    }
};

////////////////////////////////////////////
template <typename RT, typename P1, typename P2, typename P3, typename P4>
struct Functor<RT(P1, P2, P3, P4)> : public BaseFunctor
{
    Functor(const std::string& name)
      : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())(p1, p2, p3, p4);
	}
};


////////////////////////////////////////////
template < typename RT
         , typename P1
         , typename P2
         , typename P3
         , typename P4
         , typename P5>
struct Functor<RT(P1, P2, P3, P4, P5)> : public BaseFunctor
{
    Functor(const std::string& name)
      : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())(p1, p2, p3, p4, p5);
    }
};

////////////////////////////////////////////
template < typename RT
         , typename P1
         , typename P2
         , typename P3
         , typename P4
         , typename P5
         , typename P6>
struct Functor<RT(P1, P2, P3, P4, P5, P6)> : public BaseFunctor
{
	Functor(const std::string& name)
		: BaseFunctor(name)
	{}

	RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())
             (p1, p2, p3, p4, p5, p6);
	}
};

////////////////////////////////////////////
template < typename RT
         , typename P1
         , typename P2
         , typename P3
         , typename P4
         , typename P5
         , typename P6
         , typename P7>
struct Functor<RT(P1, P2, P3, P4, P5, P6, P7)> : public BaseFunctor
{
    Functor(const std::string& name)
        : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())
             (p1, p2, p3, p4, p5, p6, p7);
    }
};

////////////////////////////////////////////
template < typename RT
         , typename P1
         , typename P2
         , typename P3
         , typename P4
         , typename P5
         , typename P6
         , typename P7
         , typename P8>
struct Functor<RT(P1, P2, P3, P4, P5, P6, P7, P8)> : public BaseFunctor
{
    Functor(const std::string& name)
        : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())
             (p1, p2, p3, p4, p5, p6, p7, p8);
    }
};

////////////////////////////////////////////
template < typename RT
         , typename P1
         , typename P2
         , typename P3
         , typename P4
         , typename P5
         , typename P6
         , typename P7
         , typename P8
         , typename P9>
struct Functor<RT(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public BaseFunctor
{
    Functor(const std::string& name)
        : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())
             (p1, p2, p3, p4, p5, p6, p7, p8, p9);
    }
};

////////////////////////////////////////////
template < typename RT
         , typename P1
         , typename P2
         , typename P3
         , typename P4
         , typename P5
         , typename P6
         , typename P7
         , typename P8
         , typename P9
         , typename P10>
struct Functor<RT(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)> : public BaseFunctor
{
    Functor(const std::string& name)
        : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6,
                  P7 p7, P8 p8, P9 p9, P10 p10)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())
             (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
};

////////////////////////////////////////////
template < typename RT
         , typename P1
         , typename P2
         , typename P3
         , typename P4
         , typename P5
         , typename P6
         , typename P7
         , typename P8
         , typename P9
         , typename P10
         , typename P11>
struct Functor<RT(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)> : public BaseFunctor
{
    Functor(const std::string& name)
        : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6,
                  P7 p7, P8 p8, P9 p9, P10 p10, P11 p11)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())
             (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
    }
};

////////////////////////////////////////////
template < typename RT
         , typename P1
         , typename P2
         , typename P3
         , typename P4
         , typename P5
         , typename P6
         , typename P7
         , typename P8
         , typename P9
         , typename P10
         , typename P11
         , typename P12>
struct Functor<RT(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)> : public BaseFunctor
{
    Functor(const std::string& name)
        : BaseFunctor(name)
    {}

    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6,
                  P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12)
    {
      return GlobalMockObject::instance.invoke<RT>(getName())
             (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
    }
};

////////////////////////////////////////////
template <typename RT>
struct Functor<RT(...)> : public BaseFunctor
{
	Functor(const std::string& name)
		: BaseFunctor(name)
	{}

	RT operator()(const RefAny& p01 = RefAny(), const RefAny& p02 = RefAny(),
         const RefAny& p03 = RefAny(), const RefAny& p04 = RefAny(),
         const RefAny& p05 = RefAny(), const RefAny& p06 = RefAny(), 
         const RefAny& p07 = RefAny(), const RefAny& p08 = RefAny(), 
         const RefAny& p09 = RefAny(), const RefAny& p10 = RefAny(), 
         const RefAny& p11 = RefAny(), const RefAny& p12 = RefAny())
    {
      return GlobalMockObject::instance.invoke<RT>(getName())
             (p01, p02, p03, p04, p05, p06, p07, p08, p09, p10, p11, p12);
	}
};

////////////////////////////////////////////
template <typename RT, typename P1>
struct Functor<RT(P1,...)> : public BaseFunctor
{
	Functor(const std::string& name)
		: BaseFunctor(name)
	{}

	RT operator()(P1 p01, const RefAny& p02 = RefAny(),
         const RefAny& p03 = RefAny(), const RefAny& p04 = RefAny(),
         const RefAny& p05 = RefAny(), const RefAny& p06 = RefAny(), 
         const RefAny& p07 = RefAny(), const RefAny& p08 = RefAny(), 
         const RefAny& p09 = RefAny(), const RefAny& p10 = RefAny(), 
         const RefAny& p11 = RefAny(), const RefAny& p12 = RefAny())
    {
		return GlobalMockObject::instance.invoke<RT>(getName())
				(p01, p02, p03, p04, p05, p06, p07, p08, p09, p10, p11, p12);
	}
};

MOCKCPP_NS_END

////////////////////////////////////////////
#define MOCKABLE(function) MOCKCPP_NS::Functor<typeof(function)>(#function)
#define MOCKER(function) MOCKCPP_NS::GlobalMockObject::instance.method(#function)


#endif

