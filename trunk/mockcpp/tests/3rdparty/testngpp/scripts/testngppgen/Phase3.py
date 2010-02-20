#!/usr/bin/python

import re
import codecs

from Phase1Result import *
from PreprocessScopeParser import *
from ElemParser import ElemParser

from FixtureParser import FixtureParser

from Message import *

fixture_re1  = re.compile( \
   r'''^\s*FIXTURE\s*\(\s*(?P<fixtureId>[A-Za-z_][A-Za-z0-9_]*)\s*(,\s*(?P<fixtureName>[^\)]+))?\s*\)\s*''', \
   re.UNICODE)

fixture_re2  = re.compile( \
   r'''^\s*(struct|class)\s+(?P<fixtureId>[A-Za-z_][A-Za-z0-9_]*)\s*:\s*public\s+((TESTNGPP_NS|TESTCPP_NS|testngpp|testcpp)\s*::)?\s*TestFixture\s*$''' )

fixture_re3  = re.compile( \
   r'''^\s*(struct|class)\s+(?P<fixtureId>[A-Za-z_][A-Za-z0-9_]*)\s*:\s*public\s+((CxxTest)\s*::)?\s*TestSuite\s*$''' )
##########################################################
def is_fixture_def(line):
   matched = fixture_re1.match(line)
   if matched:
      return "Test"+matched.group("fixtureId"), matched.group("fixtureName")

   matched = fixture_re2.match(line)
   if matched:
      return matched.group("fixtureId"), None

   matched = fixture_re3.match(line)
   if matched:
      return matched.group("fixtureId"), None

   return None
   
##########################################################
class GlobalParser:
   def __init__(self, file):
      self.file = file
      self.tag = None

   #######################################################
   def is_elem_def(self, content):
      return is_fixture_def(content)

   #######################################################
   def __is_fixture_tag(self, tag):
      return tag.get_tag() == "fixture"

   #######################################################
   def handle_tag(self, tag):
      self.__report_useless_tag()
      if self.__is_fixture_tag(tag):
         self.tag = tag
      else:
         warning(self.file, tag, "unknown annotation @" + tag.get_tag())

   #######################################################
   def __report_useless_tag(self):
      if self.tag != None:
         warning(self.file, self.tag, "useless annotation @" + self.tag.get_tag())

      self.tag = None

   #######################################################
   def verify_scope(self, tag):
      return True

   #######################################################
   def create_elem_parser(self, elem_name, scope, file, line):
      tag = self.tag
      self.tag = None
      return FixtureParser(elem_name, file, line, tag)

   #######################################################
   def get_type_name(self):
      return "fixture"

   #######################################################
   def parse_line(self, line):
      self.__report_useless_tag()
      return None

   #######################################################
   def get_container(self):
      return None

##########################################################
def phase3(globalScope, file):
   return PreprocessScopeParser(file, globalScope, GlobalParser(file), ElemParser, None).parse()

