

#include <cxxtest/TestSuite.h>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/internal/Error.h>
#include <testngpp/runner/TagsFilters.h>
#include <testngpp/runner/TagsParser.h>
#include <testngpp/internal/Taggable.h>

USING_TESTNGPP_NS

class TestTagsParser: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
   }
   
   void tearDown()
   {
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   struct TaggableObj0 : public Taggable
   {
      unsigned int numberOfTags() const
      {
         return 0;
      }
      
      const char** getTags() const
      {
         static const char* tags[] = {0};
         return tags;
      }
   };
   
   struct TaggableObj1 : public Taggable
   {
      unsigned int numberOfTags() const
      {
         return 1;
      }
      
      const char** getTags() const
      {
         static const char* tags[] = {"tag1"};
         return tags;
      }
   };

   struct TaggableObj2 : public Taggable
   {
      unsigned int numberOfTags() const
      {
         return 2;
      }
      
      const char** getTags() const
      {
         static const char* tags[] = {"tag2", "tag4"};
         return tags;
      }
   };

   struct TaggableObj3 : public Taggable
   {
      unsigned int numberOfTags() const
      {
         return 2;
      }
      
      const char** getTags() const
      {
         static const char* tags[] = {"tag3", "tag5"};
         return tags;
      }
   };
   
   
   struct TaggableObj4 : public Taggable
   {
      unsigned int numberOfTags() const
      {
         return 2;
      }
      
      const char** getTags() const
      {
         static const char* tags[] = {"tag2", "tag5"};
         return tags;
      }
   };
   
   void testShouldBeAbleToParseSingleGroup()
   {
      std::string tagsSpec("tag1 tag2 tag3");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      
      TS_ASSERT(filter->startOnNext());
      
      TaggableObj0 obj0;
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(!filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TaggableObj1 obj1;
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TaggableObj2 obj2;
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TaggableObj3 obj3;
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TaggableObj4 obj4;
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));

      TS_ASSERT(!filter->startOnNext());
      
      delete filter;
   }

   void testShouldBeAbleToParseMultiGroups()
   {
      std::string tagsSpec("tag1 tag2>tag3 tag4>tag5");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      
      TaggableObj0 obj0;
      TaggableObj1 obj1;
      TaggableObj2 obj2;
      TaggableObj3 obj3;
      TaggableObj4 obj4;
      
      ///////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(!filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));

      ///////////////////////////////////////////////////      
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(!filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(filter->hasBeenFiltered(&obj4));
      
      ////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());

      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(!filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(filter->hasBeenFiltered(&obj4));
      
      TS_ASSERT(!filter->startOnNext());
      
      delete filter;  
   }
   
   void testShouldBeAbleToRecognizeMatchAll1()
   {
      std::string tagsSpec("*>tag1 tag2>tag4");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      
      TaggableObj0 obj0;
      TaggableObj1 obj1;
      TaggableObj2 obj2;
      TaggableObj3 obj3;
      TaggableObj4 obj4;
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));

      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));

      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(filter->hasBeenFiltered(&obj4));
      
      TS_ASSERT(!filter->startOnNext());
      
      delete filter;  
   }
   
   void testShouldBeAbleToRecognizeMatchAll2()
   {
      std::string tagsSpec("tag1 tag2>*>tag5");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      TaggableObj0 obj0;
      TaggableObj1 obj1;
      TaggableObj2 obj2;
      TaggableObj3 obj3;
      TaggableObj4 obj4;
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(filter->hasBeenFiltered(&obj4));
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(filter->hasBeenFiltered(&obj4));
      
      TS_ASSERT(!filter->startOnNext());
      
      delete filter;  
   }
   
   void testShouldBeAbleToRecognizeMatchAll3()
   {
      std::string tagsSpec("tag1 tag2>tag3 tag4>*");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      
      TS_ASSERT(filter->startOnNext());
      TS_ASSERT(filter->startOnNext());
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->startOnNext());
      
      delete filter;  
   }
   
   void testShouldBeAbleToRecognizeMatchAllNotInTopScope()
   {
      std::string tagsSpec("tag1 tag2>tag3 tag4>(*)");
      
      TS_ASSERT_THROWS(TagsParser::parse(tagsSpec), TESTNGPP_NS::Error);
   }

   void testShouldBeAbleToRecognizeSignOfNoTag()
   {
      std::string tagsSpec("tag1 $ >tag3 tag4>*");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      
      TaggableObj0 obj0;
      TaggableObj1 obj1;
      TaggableObj2 obj2;
      TaggableObj3 obj3;
      TaggableObj4 obj4;
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));
      
      TS_ASSERT(!filter->startOnNext());
      
      delete filter;  
   }
   
   void testShouldBeAbleToHandleMatchAll()
   {
      std::string tagsSpec("*");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      
      TaggableObj0 obj0; // $
      TaggableObj1 obj1; // tag1
      TaggableObj2 obj2; // tag2, tag4
      TaggableObj3 obj3; // tag3, tag5
      TaggableObj4 obj4; // tag2, tag5
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));
      
      delete filter;
      
   }
   
   void testDollarSignShouldNotBeUsedInAndGroup()
   {
      std::string tagsSpec("[tag1 $] >tag3 tag4>*");
      
      TS_ASSERT_THROWS(TagsParser::parse(tagsSpec), TESTNGPP_NS::Error);
   }
   
   void testShouldBeAbleToRecognizeAndGroup()
   {
      std::string tagsSpec("([tag2 tag5] $) > tag4 > * ");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      
      TaggableObj0 obj0; // $
      TaggableObj1 obj1; // tag1
      TaggableObj2 obj2; // tag2, tag4
      TaggableObj3 obj3; // tag3, tag5
      TaggableObj4 obj4; // tag2, tag5
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(filter->hasBeenFiltered(&obj4));
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(filter->hasBeenFiltered(&obj4));
      
      TS_ASSERT(!filter->startOnNext());
      
      delete filter;  
   }
   
   void testShouldBeAbleToRecogonizeAllObjWithTags()
   {
      std::string tagsSpec("^$");
      
      TagsFilters* filter = TagsParser::parse(tagsSpec);
      
      TS_ASSERT(0 != filter);
      
      TaggableObj0 obj0; // $
      TaggableObj1 obj1; // tag1
      TaggableObj2 obj2; // tag2, tag4
      TaggableObj3 obj3; // tag3, tag5
      TaggableObj4 obj4; // tag2, tag5
      
      /////////////////////////////////////////////////////
      TS_ASSERT(filter->startOnNext());
      
      TS_ASSERT(!filter->shouldBeFilteredThisTime(&obj0));
      TS_ASSERT(!filter->shouldBeFiltered(&obj0));
      TS_ASSERT(!filter->isPreFiltered(&obj0));
      TS_ASSERT(!filter->hasBeenFiltered(&obj0));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj1));
      TS_ASSERT(filter->shouldBeFiltered(&obj1));
      TS_ASSERT(!filter->isPreFiltered(&obj1));
      TS_ASSERT(!filter->hasBeenFiltered(&obj1));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj2));
      TS_ASSERT(filter->shouldBeFiltered(&obj2));
      TS_ASSERT(!filter->isPreFiltered(&obj2));
      TS_ASSERT(!filter->hasBeenFiltered(&obj2));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj3));
      TS_ASSERT(filter->shouldBeFiltered(&obj3));
      TS_ASSERT(!filter->isPreFiltered(&obj3));
      TS_ASSERT(!filter->hasBeenFiltered(&obj3));
      
      TS_ASSERT(filter->shouldBeFilteredThisTime(&obj4));
      TS_ASSERT(filter->shouldBeFiltered(&obj4));
      TS_ASSERT(!filter->isPreFiltered(&obj4));
      TS_ASSERT(!filter->hasBeenFiltered(&obj4));
      
      /////////////////////////////////////////////////////
      TS_ASSERT(!filter->startOnNext());
      
      delete filter;
   }
};
