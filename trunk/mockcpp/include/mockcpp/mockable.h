
#ifndef __MOCKCPP_MOCKABLE_H
#define __MOCKCPP_MOCKABLE_H

#ifdef __cplusplus
#  include <Functor.h>
#  include <boost/typeof/typeof.hpp>
#  define MOCKABLE(function) MOCKCPP_NS::Functor<BOOST_TYPEOF(function)> function(#function, __FUNCTION__)
#  define MCALL(function) MOCKCPP_NS::Functor<typeof(function)>(#function, __FUNCTION__) 
#else
#  define MOCKABLE(function)
#  define MCALL(function) function
#endif

#endif
