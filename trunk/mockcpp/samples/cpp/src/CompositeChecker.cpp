
#include <CompositeChecker.h>


namespace cpp
{

   CompositeChecker::CompositeChecker(CompositeChecker::List* compositedCheckers)
        : checkers(compositedCheckers)
   {}

   bool CompositeChecker::check(const std::string& user) const
   {
       CompositeChecker::List::const_iterator i = checkers->begin();
       for(; i != checkers->end(); i++)
       {
           (*i)->check(user);
       }

       return false;
   }
}
