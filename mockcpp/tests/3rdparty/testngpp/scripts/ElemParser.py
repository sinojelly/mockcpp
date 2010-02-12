#!/usr/bin/python

from PreprocessScope import PreprocessScope
from PreprocessScopeParser import PreprocessScopeParser

from Phase1Result import *

from Message import *

class ElemParser:
   #######################################################
   def __init__(self, file, parser, container):
      self.file   = file
      self.parser = parser     # for fixture
      self.elem_parser = None
      self.sub_scopes = []
      self.done = None
      self.last_line = None
      self.container = container

   #######################################################
   def __handle_tag(self, tag):
      self.parser.handle_tag(tag)

   #######################################################
   def __handle_scope(self, scope):
      if self.parser.verify_scope(scope):
         self.sub_scopes.append(scope)

   #######################################################
   def __create_elem_parser(self, elem_name, line):
      elem_parser = self.parser.create_elem_parser(elem_name,\
                       self.container.get_scope(), \
                       self.file, \
                       line.get_line_number())

      return ElemParser(self.file, elem_parser, elem_parser.get_container())
   
   #######################################################
   def __parse_normal_line(self, line):
      return self.parser.parse_line(line)

   #######################################################
   def __parse_by_myself(self, line):
      if isinstance(line, Tag):
         self.__handle_tag(line)
         return None

      if isinstance(line, PreprocessScope):
         self.__handle_scope(line)
         return None

      elem_name = self.parser.is_elem_def(line.get_content())
      if elem_name:
         self.elem_parser = self.__create_elem_parser(elem_name, line)
         return None

      return self.__parse_normal_line(line)

   #######################################################
   def __parse_elem(self, line):
      elem = self.elem_parser.parse_line(line)
      if elem:
         self.container.add_elem(elem)
         self.elem_parser = None

      return None

   #######################################################
   def __parse_scope(self, scope):
      return PreprocessScopeParser(self.file, scope, self.parser, \
               self.__class__, self.container.get_scope()).parse()

   #######################################################
   def __handle_sub_scopes(self):
      for scope in self.sub_scopes:
         self.container.add_sub_scope(self.__parse_scope(scope))

      self.sub_scopes = []

   #######################################################
   def parse_line(self, line):
      if self.done:
         fatal(self.file, line, "internal error")

      self.last_line = line

      if self.elem_parser:
         return self.__parse_elem(line)

      self.done = self.__parse_by_myself(line)
      if self.done:
         self.__handle_sub_scopes() 

      return self.done

   #######################################################
   def incompleted_elem_def(self):
      return self.elem_parser != None

   #######################################################
   def get_unhandled_sub_scopes(self):
      return self.sub_scopes

##########################################################
