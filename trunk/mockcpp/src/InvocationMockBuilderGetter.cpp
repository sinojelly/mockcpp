
#include <InvocationMockBuilderGetter.h>
#include <InvocationMockerContainer.h>
#include <StubsMatcher.h>
#include <ExpectsMatcher.h>
#include <InvokedTimesMatcher.h>
#include <InvocationTimesMatcher.h>
#include <InvokedTimesRecorder.h>
#include <SimpleInvocationRecorder.h>
#include <InvocationMocker.h>
#include <DefaultMatcher.h>
#include <Method.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
InvocationMockBuilderGetter::
InvocationMockBuilderGetter(InvocationMockerContainer* container, Method* m)
	: invocationMockerContainer(container), method(m)
{

}
///////////////////////////////////////////////////////////
InvocationMockBuilderGetter::~InvocationMockBuilderGetter()
{
}

//////////////////////////////////////////////////////////
WorkingBuilder InvocationMockBuilderGetter::stubs()
{
    InvocationMocker* mocker = new InvocationMocker(method);
    mocker->addMatcher(new StubsMatcher);
    mocker->addMatcher(new InvokedTimesMatcher(new SimpleInvocationRecorder));

    invocationMockerContainer->addInvocationMocker(mocker);

    return WorkingBuilder(mocker);
}

//////////////////////////////////////////////////////////
WorkingBuilder InvocationMockBuilderGetter::expects(Matcher* matcher)
{
    InvocationMocker* mocker = new InvocationMocker(method);

    InvokedTimesRecorder* recorder = new SimpleInvocationRecorder;
    InvocationTimesMatcher* itMatcher = dynamic_cast<InvocationTimesMatcher*>(matcher);
    if (itMatcher != 0)
    {
      itMatcher->setInvokedTimesReader(recorder);
    }

    mocker->addMatcher(new ExpectsMatcher(matcher));
    mocker->addMatcher(new InvokedTimesMatcher(recorder));

    invocationMockerContainer->addInvocationMocker(mocker);

    return WorkingBuilder(mocker);
}

//////////////////////////////////////////////////////////
DefaultBuilder InvocationMockBuilderGetter::defaults()
{
    InvocationMocker* mocker = new InvocationMocker(method);
    mocker->addMatcher(new DefaultMatcher);

    invocationMockerContainer->addDefaultInvocationMocker(mocker);

    return DefaultBuilder(mocker);
}

//////////////////////////////////////////////////////////

MOCKCPP_NS_END

