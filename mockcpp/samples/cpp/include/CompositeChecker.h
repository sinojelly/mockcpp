
#ifndef __CPP_COMPOSITE_CHECKER_H
#define __CPP_COMPOSITE_CHECKER_H

#include <Checker.h>
#include <list>

namespace cpp
{
   class CompositeChecker : public Checker
   {
   public:
       typedef std::list<Checker*> List;

   public:
       CompositeChecker(List*);

       bool check(const std::string& user) const;

   private:
       List* checkers; 
   };
}

#endif
