
#ifndef __MOCKCPP_MOKC_H
#define __MOCKCPP_MOKC_H

#ifdef __cplusplus
#  include <ChainingMockHelper.h>
#  include <Functor.h>

#  define MOCKER(function) MOCKCPP_NS::GlobalMockObject::instance.method(#function)

USING_MOCKCPP_NS

#endif

#endif

