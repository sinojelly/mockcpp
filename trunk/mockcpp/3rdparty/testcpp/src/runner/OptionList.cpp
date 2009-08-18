
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <OptionList.h>

TESTCPP_NS_START

////////////////////////////////////////////////////
static void
parseOpt(OptionList* This, int argc, char** argv, const char* optstr)
{
   int c;
  	optind = 1;
   while ((c = ::getopt (argc, argv, optstr)) != -1)
   {
      char buf[2];
      sprintf(buf, "%c", c=='?'?optopt:c);

      This->options.push_back(
          OptionList::Option(buf, std::string(optarg==0?"":optarg)));
   }
}

////////////////////////////////////////////////////
void
OptionList::parse(int argc, char** argv, const char* optstr)
{
   opterr = 0;
   options.clear();
   args.clear();

   while(1)
   {
      optind = 1;

      parseOpt(this, argc, argv, optstr);

      argc -= optind;
      argv += optind;
      if(argc <= 0)
      {
        break;
      }

      args.push_back(argv[0]);
   }
}

////////////////////////////////////////////////////

TESTCPP_NS_END

