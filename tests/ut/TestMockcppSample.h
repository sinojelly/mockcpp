#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>
#include <mockcpp/mockcpp.hpp>

struct Interface
{
    virtual int method() = 0;
    static int func() { return 0; }
    virtual ~Interface(){}
};

int func_stub()
{
    return 1000;
}

struct Interface2
{
    virtual ~Interface2(){}
    virtual int method1() {
        return 1;
    }
    int method2() {
        return 2;
    }
};

int func_client(Interface2* intf) 
{
    return intf->method2();
}

FIXTURE(mockcpp_sample, mockcpp samples)
{
    TEST(test_method_mocker)
    {
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, method)
            .expects(once())
            .will(returnValue(10));
        ASSERT_EQ(10, mocker->method());
        mocker.verify();
    }

    TEST(test_func_mocker)
    {
        MOCKER(Interface::func)
            .expects(once())
            .will(returnValue(10));
        ASSERT_EQ(10, Interface::func());
        GlobalMockObject::verify();
    }
	
    TEST(test will invoke)
    {
        MOCKER(Interface::func)
            .expects(once())
            .will(invoke(func_stub));
        ASSERT_EQ(1000, Interface::func());
        GlobalMockObject::verify();
    }

    // mock的类不全是虚方法, 如果调用到非虚方法，则mock框架不会报错，而是调用真正的非虚方法，可能出现内存非法访问。
    // 从设计解耦的角度讲，应尽可能面向接口编程，而需要mock的也都是接口。接口里面的方法全是虚方法。所以不存在这种情况。
    // 如果实际使用中，用来mock带有非虚方法，甚至含有成员变量的类，则可能出现问题。需要小心。
    TEST(call a method not mocked) 
    {
        MockObject<Interface2> mocker;
        MOCK_METHOD(mocker,  method1)
            .defaults()
            .will(returnValue(100));
        ASSERT_EQ(2, func_client(mocker));

    }	
};
