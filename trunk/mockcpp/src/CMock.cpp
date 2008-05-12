
#include <CMock.h>

MOCKCPP_NS_START

namespace {
static ChainableMockObject* g_globalMockContext = 0;
}

ChainableMockObject* getGlobalMockContext()
{
    if (g_globalMockContext == 0)
    {
      g_globalMockContext = new ChainableMockObject("", 0);
    }

    return g_globalMockContext;
}

void globalMockContextVerifyAndReset()
{
    if (g_globalMockContext == 0)
    {
      return;
    }

    try {
      g_globalMockContext->verify();
      g_globalMockContext->reset();
    }
    catch(...)
    {
      g_globalMockContext->reset();
      throw;
    }
}

MOCKCPP_NS_END

