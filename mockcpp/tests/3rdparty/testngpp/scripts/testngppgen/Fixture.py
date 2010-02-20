#!/usr/bin/python

import sys
import re

from TestScope import TestScope
from AnnotationParser import AnnotationParser
from TagsParser import TagsParser
from Name import *

###########################################
class Fixture:
   ########################################
   def __init__(self, name, file, line, tag):
      self.id   = name[0]
      self.name = name[1]
      if self.name != None:
         self.name = escape_name(self.name)
      self.scope = TestScope("::", None, None)
      self.file = file
      self.line = line
      self.annotations = AnnotationParser(tag, {"tags":[]}).parse()
      self.annotations['tags'] = TagsParser(self.annotations['tags']).parse()

   ########################################
   def get_tags(self):
      return self.annotations['tags']

   ########################################
   def show(self):
      content = "FIXTURE("+self.get_name()+")"
      print content.encode('utf-8')
      self.scope.show()

   ########################################
   def set_scope(self, scope):
      pass

   ########################################
   def get_id(self):
      return self.id

   ########################################
   def get_name(self):
      if self.name:
         return self.name

      return self.id

   ########################################
   def merge(self, scope):
      self.scope.merge(scope)

   ########################################
   def add_elem(self, testcase):
      self.scope.add_elem(testcase)

   ########################################
   def add_sub_scope(self, scope):
      self.scope.add_sub_scope(scope)

   ########################################
   def get_scope(self):
      return self.scope

   ########################################
   def get_file_name(self):
      return self.file

   ########################################
   def get_line_number(self):
      return self.line

###########################################
