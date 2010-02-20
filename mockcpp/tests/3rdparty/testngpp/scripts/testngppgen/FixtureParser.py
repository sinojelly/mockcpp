#!/usr/bin/python

import sys
import re
import os
import codecs

from Phase1Result import *

from PreprocessScope import *
from Fixture import Fixture

from TestCaseParser import TestCaseParser
from PreprocessScopeParser import *

from Message import *

testcase_re1 = re.compile( r'^\s*TEST\s*\(\s*(?P<testcaseName>[^\)]+)\s*\)\s*$' , re.UNICODE)
testcase_re2 = re.compile( r'^\s*void\s+(?P<testcaseId>test[A-Za-z0-9_]+)\s*\(\s*(void)?\s*\)\s*$')

testcase_re3 = re.compile( r'^\s*void\s+(?P<testcaseId>[A-Za-z_][A-Za-z0-9_]*)\s*\(\s*(void)?\s*\)\s*$')

##########################################################
def is_testcase_def(line):
   matched = testcase_re1.match(line) 
   if matched:
      return None, matched.group("testcaseName")

   matched = testcase_re2.match(line)
   if matched:
      return matched.group("testcaseId"), None

   return None

##########################################################
def might_be_testcase_def(line):
   matched = testcase_re3.match(line)
   if matched:
      return matched.group("testcaseId"), None

   return None
   
##########################################################
class FixtureParser:
   def __init__(self, name, file, line, tag):
      self.numberOfUnclosedBraces = 0
      self.begin = True
      self.end = None
      self.done = None
      self.file = file
      self.line = line
      self.tag = None

      self.container = Fixture(name, self.file, self.line, tag)

   #######################################################
   def get_container(self):
      return self.container

   #######################################################
   def __might_be_elem_def(self, content):
      return might_be_testcase_def(content)
   
   #######################################################
   def __has_test_tag(self):
      if self.tag != None and self.tag.get_tag() == "test":
         return True

      return None

   #######################################################
   def is_elem_def(self, content):
      id = self.__might_be_elem_def(content)
      if id and self.__has_test_tag():
         return id

      return is_testcase_def(content)

   #######################################################
   def handle_tag(self, tag):
      self.__report_useless_tag()
      self.tag = tag

   #######################################################
   def __report_useless_tag(self):
      if self.tag != None:
         warning(self.file, self.tag, "useless tag definition @" + self.tag.get_tag())

      self.tag = None

   #######################################################
   def verify_scope(self, tag):
      self.__report_useless_tag()
      return True

   #######################################################
   def create_elem_parser(self, elem_name, scope, file, line):
      parser = TestCaseParser(elem_name, scope, file, line, self.tag)
      self.tag = None
      return parser

   #######################################################
   def get_type_name(self):
      return "fixture"

   #######################################################
   def __handle_space(self, line, c):
      if c.isspace():
         return True

      return None

   #######################################################
   def __handle_done(self, line, c):
      if not self.done:
         return None

      fatal(self.file, line, "unexpected char '" + c + "'")

   #######################################################
   def __handle_begin(self, line, c):
      if not self.begin:
         return None
      
      if c == '{':
         self.numberOfUnclosedBraces = 1
         self.begin = None
         return True

      report_expect_char(self.file, line, "{", c)

   #######################################################
   def __handle_end(self, line, c):
      if not self.end:
         return None

      if c == ';':
         self.done = True
         return True

      report_expect_char(self.file, line, ";", c)

   #######################################################
   def __handle_others(self, line, c):
      if c == '{':
         self.numberOfUnclosedBraces += 1
      elif c == '}':
         self.numberOfUnclosedBraces -= 1
         if self.numberOfUnclosedBraces == 0:
            self.end = True

   #######################################################
   def __handle_char(self, line, c):
      self.__handle_space(line, c) or \
      self.__handle_done(line, c) or \
      self.__handle_begin(line, c) or \
      self.__handle_end(line, c)   or \
      self.__handle_others(line, c)

   #######################################################
   def parse_line(self, line):
      self.__report_useless_tag()
      for c in line.get_content():
         self.__handle_char(line, c)

      if self.done:
         return self.container

      return None

##########################################################

