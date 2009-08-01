
#ifndef __MOCKCPP_CONFIG_H
#define __MOCKCPP_CONFIG_H

#define MOCKCPP_NO_NAMESPACE 0

#define MOCKCPP_MAX_PARAMETERS 12

#define MOCKCPP_MAX_VTBL_SIZE 10

#define MOCKCPP_ALLOW_MULTI_INHERITANCE 1
#define MOCKCPP_MAX_INHERITANCE 2

///////////////////////////////////////////////////
#ifndef MOCKCPP_MAX_PARAMETERS
#define MOCKCPP_MAX_PARAMETERS 6
#endif

#if MOCKCPP_MAX_PARAMETERS > 15
#error "MOCKCPP_MAX_PARAMETERS is too many, probably you should refine your design"
#endif
///////////////////////////////////////////////////
#ifndef MOCKCPP_MAX_VTBL_SIZE
#define MOCKCPP_MAX_VTBL_SIZE 10
#endif

#if MOCKCPP_MAX_VTBL_SIZE > 50
#error "MOCKCPP_MAX_VTBL_SIZE is too big, probably you should refine your design"
#endif

///////////////////////////////////////////////////
#ifndef MOCKCPP_MAX_INHERITANCE
#define MOCKCPP_MAX_INHERITANCE 1
#endif

#if MOCKCPP_MAX_INHERITANCE > 5
#error "MOCKCPP_MAX_INHERITANCE is too many, probably you should refine your design"
#endif
///////////////////////////////////////////////////


#endif
