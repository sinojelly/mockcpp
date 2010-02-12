#!/usr/bin/python

from Phase1Result import *
from TestCase import *
from PreprocessScope import *

from Message import *





##########################################################
class TestCaseParser:
   #######################################################
   def __init__(self, name, scope, file, line, tag):
      self.verify_testcase_tag(tag)
      self.testcase = TestCase(name, scope, file, line, tag)
      self.begin = True
      self.done = None
      self.numberOfUnclosedBraces = 0
      self.file = file

   #######################################################
   def verify_testcase_tag(self, tag):
      if tag != None and tag.get_tag() != "test":
         warning(self.file, tag, "unknown annotation @" + tag.get_tag())

   #######################################################
   def get_container(self):
      return None

   #######################################################
   def is_elem_def(self, content):
      return None

   #######################################################
   def handle_space(self, line, c):
      if c.isspace():
         return True

      return None
      
   #######################################################
   def handle_done(self, line, c):
      if not self.done:
         return None

      fatal(self.file, line, "unexpected char '" + c + "' in test case definition")
      
   #######################################################
   def handle_begin(self, line, c):
      if not self.begin:
         return None

      if c == '{':
         self.numberOfUnclosedBraces = 1
         self.begin = None
         return True

      report_expect_char(self.file, line, "{", c)
  
   #######################################################
   def handle_others(self, line, c):
      if c == '{':
         self.numberOfUnclosedBraces += 1
      elif c == '}':
         self.numberOfUnclosedBraces -= 1
         if self.numberOfUnclosedBraces == 0:
            self.done = True
      
   #######################################################
   def handle_char(self, line, c):
      self.handle_space(line, c) or \
      self.handle_done(line, c) or \
      self.handle_begin(line, c) or \
      self.handle_others(line, c)

   #######################################################
   def parse_line(self, line):
      if self.done:
         fatal(self.file, line, "internal error while parsing in test case")

      for c in line.get_content():
         self.handle_char(line, c)

      if self.done:
         return self.testcase

      return None

   #######################################################
   def handle_tag(self, tag):
      warning(self.file, tag, "annotation is not allowed in testcase definition")

##########################################################
