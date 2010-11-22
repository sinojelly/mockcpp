#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>
#include <mockcpp/mockcpp.hpp>

struct Interface
{
    virtual int method() = 0;
    static int func() { return 0; }
    virtual ~Interface(){}
};


FIXTURE(mockcpp_sample, test no mem leak)
{
public:    
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
};