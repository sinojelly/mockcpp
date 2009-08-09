
#ifndef __MOCKCPP_H
#define __MOCKCPP_H

#if !MOCKCPP_NO_NAMESPACE
# define MOCKCPP_NS mockcpp
# define MOCKCPP_NS_START namespace MOCKCPP_NS{
# define MOCKCPP_NS_END }
# define USING_MOCKCPP_NS using namespace MOCKCPP_NS;
#else
# define MOCKCPP_NS 
# define MOCKCPP_NS_START 
# define MOCKCPP_NS_END 
# define USING_MOCKCPP_NS 
#endif


#endif // __MOCKCPP_H

