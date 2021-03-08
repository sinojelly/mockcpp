#!/usr/bin/python

import sys

from testngppstgen.Generator import generate, usage

##########################################################
if __name__ == "__main__":
   if len(sys.argv) < 2:
      usage()
      sys.exit(1)

   generate(sys.argv[1:])
