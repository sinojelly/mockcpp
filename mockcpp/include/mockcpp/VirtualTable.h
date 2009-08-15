
#ifndef __MOCKCPP_VIRTUAL_TABLE_H
#define __MOCKCPP_VIRTUAL_TABLE_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct IndexInvokableGetter;
class VirtualTableImpl;

struct VirtualTable
{
   VirtualTable(IndexInvokableGetter* getter, unsigned int numberOfVptr = 1);

   ~VirtualTable();

   void* toPointerToInterface() const;

   void addMethod(void* methodAddr, unsigned int indexOfVtbl, unsigned int indexofVptr = 0);

   void reset();

   static IndexInvokableGetter* getInvokableGetter(void* Caller, unsigned int indexOfVptr);

private:
	VirtualTableImpl* This;
};

MOCKCPP_NS_END

#endif

