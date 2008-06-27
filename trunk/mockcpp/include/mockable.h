
#ifndef __MOCKCPP_MOCKABLE_H
#define __MOCKCPP_MOCKABLE_H

#ifdef __cplusplus
#  include <Functor.h>
#  define MOCKABLE(function) MOCKCPP_NS::Functor<typeof(function)> function(#function)
#  define MCALL(function) MOCKCPP_NS::Functor<typeof(function)>(#function) 
#else
#  define MOCKABLE(function)
#  define MCALL(function) function
#endif

#endif
