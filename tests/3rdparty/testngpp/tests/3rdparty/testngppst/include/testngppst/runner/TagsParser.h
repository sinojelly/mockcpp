
#ifndef __TESTNGPPST_TAGS_PARSER_H
#define __TESTNGPPST_TAGS_PARSER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TagsFilters;

struct TagsParser
{
    static TagsFilters* parse(const std::string& tagsSpec);
};

TESTNGPPST_NS_END

#endif
