
#ifndef __TESTNGPP_TAGS_FILTER_RESULT_COLLECTOR_H
#define __TESTNGPP_TAGS_FILTER_RESULT_COLLECTOR_H

#include <string>

#include <testngpp/testngpp.h>

#include <testngpp/runner/TestSuiteResultCollector.h>

TESTNGPP_NS_START

struct TaggableObjFilter;

struct TagsFilterResultCollector
   : public TestSuiteResultCollector
{
   virtual void startTagsFiltering(const TaggableObjFilter*) = 0;
   virtual void endTagsFiltering(const TaggableObjFilter*) = 0;

   virtual ~TagsFilterResultCollector() {}
};

TESTNGPP_NS_END

#endif

