
#include <mockcpp/mockcpp.h>
#include <typeinfo>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////////////////
namespace
{
#if defined(__GNUC__)
   const unsigned int EXTRA_VTBL_SLOT = 2;
#elif defined(_MSC_VER)
   const unsigned int EXTRA_VTBL_SLOT = 1;
#endif
   const unsigned int SLOTS_PER_VTBL = MOCKCPP_MAX_VTBL_SIZE + EXTRA_VTBL_SLOT;
}

///////////////////////////////////////////////////////////////////////
void** createVtbls(unsigned int numberOfVptr)
{
	return new void*[numberOfVptr * SLOTS_PER_VTBL];
}

///////////////////////////////////////////////////////////////////////
unsigned int getRealVtblIndex(unsigned int indexOfVptr, unsigned int indexOfVtbl)
{
   return indexOfVptr * SLOTS_PER_VTBL + EXTRA_VTBL_SLOT + indexOfVtbl ;
}

///////////////////////////////////////////////////////////////////////
void initializeVtbls(void** vptr, void**vtbl, unsigned int numberOfVtpr, const std::type_info& info)
{   
   for(unsigned int i=0; i<numberOfVtpr; i++)
   {
      int base = i*SLOTS_PER_VTBL;

#if defined(__GNUC__)
      vtbl[base + 0] = (void*)(-1*(sizeof(void*)*i));
      vtbl[base + 1] = (void*)&info;
#elif defined(_MSC_VER)
	  //FIXME
	  vtbl[base + 0] = 0;
#endif

      vptr[i] = (void*)&vtbl[base + EXTRA_VTBL_SLOT];
   }
}
///////////////////////////////////////////////////////////////////////


MOCKCPP_NS_END
