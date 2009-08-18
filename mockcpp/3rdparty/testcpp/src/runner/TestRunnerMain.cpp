
#include <iostream>

#include <testcpp/runner/TestRunner.h>
#include <OptionList.h>

USING_TESTCPP_NS

void usage(char * program)
{
   std::cerr << "usage: " 
             << program 
             << " [ -Lsearchingpath ... ] [ -llistener ... ] [ testsuite ... ]" << std::endl;
   exit(1);
}

////////////////////////////////////////////////////////////
static
void getSpecifiedOptions( const std::string& option
                        , TestRunner::StringList& results
                        , OptionList& options)
{
   OptionList::Options::const_iterator i = options.options.begin();
   for(; i != options.options.end(); i++)
   {
      if(i->first == option && i->second.size() > 0)
      {
         results.push_back(i->second);
      }
   }
}

////////////////////////////////////////////////////////////
static
void getListeners(TestRunner::StringList& listeners
                        , OptionList& options)
{
   getSpecifiedOptions("l", listeners, options);
}

////////////////////////////////////////////////////////////
static
void getSearchingPathsOfListeners( TestRunner::StringList& paths
                                , OptionList& options)
{
   getSpecifiedOptions("L", paths, options);
}

////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
   OptionList options;

   options.parse(argc, argv, "L:l:");
   if(options.args.size() == 0)
   {
      usage("testcpp-runner");
   }

   TestRunner::StringList listeners;
   getListeners(listeners, options);   
   TestRunner::StringList searchingPathsOfListeners;
   getSearchingPathsOfListeners(searchingPathsOfListeners, options);   

   TestRunner runner;

   return runner.runTests(5, options.args, listeners
                         , searchingPathsOfListeners);
}
