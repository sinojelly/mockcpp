#ifndef __TESTNGPPST_TAGGABLE_H
#define __TESTNGPPST_TAGGABLE_H

#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////
struct Taggable
{
   virtual
   unsigned int numberOfTags() const = 0;

   virtual
   const char** getTags() const = 0;

   virtual ~Taggable() {}
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

