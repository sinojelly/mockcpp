#!/usr/bin/python

import getopt, sys
import os

from Process import process

##########################################################
class LongOptString:
   def __init__(self, optString, example):
      self.optString = optString
      self.example = example

   def toAssignable(self):
      return self.optString + '='

   def toLongOptString(self):
      return '--' + self.optString

   def toLongAssignable(self):
      return '--' + self.optString + '='

   def toUsage(self):
      return self.toLongAssignable() + self.example

##########################################################
def getAssignableOptStrings(longOpts):
   return [i.toAssignable() for i in longOpts]

##########################################################
def getUsageString(longOpts):
   return " ".join([i.toUsage() for i in longOpts])

##########################################################
def usage(longOpts):
   print "Usage:", "testngppgen", \
      getUsageString(longOpts), \
      "[-i input-encoding] [-e output-encoding] -o target testcase1 testcase2 ..."

##########################################################
def getOpt(longOpts, argv):
   try:
      return getopt.getopt(argv, 'i:e:o:', getAssignableOptStrings(longOpts))
   except getopt.GetoptError, err:
      print >> sys.stderr, str(err)
      usage(longOpts)
      sys.exit(2)

##########################################################
longOpts = []

##########################################################
def generate(argv):
   optlist, fixtures = getOpt(longOpts, argv)

   target = None
   inputEncoding = 'utf-8'
   encoding = 'utf-8'

   for o, a in optlist:
      if o == "-o":
         target = a
      elif o == "-i":
         inputEncoding = a
      elif o == "-e":
         encoding = a

   if target == None:
      usage(longOpts)
      sys.exit(1)

   absFixtures = []
   for fixture in fixtures:
      if os.path.isabs(fixture):
         absFixtures.append(fixture)
      else:
         absFixtures.append(os.path.join(os.getcwd(), fixture))

   process(target, absFixtures, inputEncoding, encoding)

##########################################################
if __name__ == "__main__":
   if len(sys.argv) < 2:
      usage(longOpts)
      sys.exit(1)

   generate(sys.argv[1:])

