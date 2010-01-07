#!/usr/bin/python

import re
import sys

##############################################
slc_tag_re = re.compile( r'^\s*//\s*@\s*(?P<tag>[A-Za-z]+)\s*(:\s*(?P<value>.*?))?\s*$' )

##############################################
class Tag:

   ###########################################
   def __init__(self, tag, value):
      self.tag = tag
      self.value = value

   ###########################################
   def get_tag(self):
      return self.tag

   ###########################################
   def get_value(self):
      return self.value

##############################################
class TagParser:

   ###########################################
   def parse(self, line):
      matched = slc_tag_re.match(line)
      if matched:
         return Tag(matched.group("tag"), matched.group("value"))

      return None
         

##############################################
class Line:

   ###########################################
   def __init__(self, content):
      self.content = content

   ###########################################
   def get_content(self):
      return self.content

##############################################
class Comment:
   pass

##############################################
class Continue:
   pass

##############################################
slc_re   = re.compile( r'^(?P<content>.*?)\/\/.*$' )
mlc_re   = re.compile( r'^(?P<content>.*?)/\*.*$' )
emlc_re  = re.compile( r'^.*?\*/(?P<rest>.*)$' )

##############################################
class CommentsEraser:

   ###########################################
   def __init__(self):
      self.in_comment = None
      self.tag_parser = TagParser()

   ###########################################
   def parse_in_comment(self, line):
      matched = emlc_re.match(line)
      if not matched:
         return Comment()

      self.in_comment = None
      return self.parse(matched.group("rest"))

   ###########################################
   def remove_single_line_comment(self, line):
      matched = slc_re.match(line)
      if not matched:
         return line 

      return matched.group("content")

   ###########################################
   def try_to_erase_comment(self, line):
      content = "".join(re.split('/\*.*?\*/', line))
      content_without_slc = self.remove_single_line_comment(content)
      matched = mlc_re.match(content_without_slc)
      if matched:
         self.in_comment = True
         return matched.group("content")

      return content_without_slc

   def parse(self, line):
      ''' @ Line
          @ Tag
          @ Comment
      '''
      tag = self.tag_parser.parse(line)
      if tag != None:
         return tag

      if self.in_comment:
         return self.parse_in_comment(line)

      result = self.try_to_erase_comment(line)
      if isinstance(result, Comment) or isinstance(result, Tag):
         return result

      return Line(result)

##############################################

line_feed_re    = re.compile( r'^.*\\$' )
##############################################
class LineReader:

   ###########################################
   def __init__(self):
      self.buffered_lines = []

   ###########################################
   def get_full_line(self, line):
      self.buffered_lines.append(line)
      full_line = "".join(self.buffered_lines)
      self.buffered_lines = []
      return full_line

   ###########################################
   def parse(self, line):
      ''' @ Line
          @ Continue
      '''
      matched = line_feed_re.match(line)
      if matched:
         self.buffered_lines.append(line[:-1])
         return Continue()

      return Line(self.get_full_line(line))

##############################################


##############################################
class LineParser:
  
   ###########################################
   def __init__(self):
      self.line_reader = LineReader()
      self.comment_eraser = CommentsEraser()

   ###########################################
   def parse(self, line):
      content = self.line_reader.parse(line)
      if not isinstance(content, Line):
         return content

      return self.comment_eraser.parse(content.get_content())

##############################################

##############################################
class Scope:

   ###########################################
   def __init__(self, parent):
      self.parent = parent

   ###########################################
   def parse(self, line):
      pass

   ###########################################
   def get_parent(self):
      return self.parent

   ###########################################
   def outside_fixture(self):
      pass

   ###########################################
   def inside_case(self):
      pass

##############################################
if_re     = re.compile( r'^\s*#\s*if\s+(?P<const_expr>.*?)\s*$' )
elif_re   = re.compile( r'^\s*#\s*elif\s+(?P<const_expr>.*?)\s*$' )
ifdef_re  = re.compile( r'^\s*#\s*ifdef\s+(?P<macro>.*?)\s*$' )
ifndef_re = re.compile( r'^\s*#\s*ifndef\s+(?P<macro>.*?)\s*$' )
macro_re  = re.compile( r'^\s*(?P<macro>[A-Za-z_]\w*)\s*$' )
else_re   = re.compile( r'^\s*#\s*else(?P<space>.*)$' )
endif_re  = re.compile( r'^\s*#\s*endif(?P<space>.*)$' )
space_re  = re.compile( r'^\s*$' )

##############################################
def get_const_expr_of_if_preprocessor(line, \
   if_preprocessor_re, expr_getter):
   matched = if_preprocessor_re.match(line.get_content())
   if not matched:
      return None

   return expr_getter(matched)

##############################################
class CompositeScope(Scope):

   ###########################################
   def __init__(self, parent):
      Scope.__init__(self, parent)
      self.scopes = []
      self.in_global = True

   ###########################################
   def get_scope(self):
      if self.in_global:
         return self

      return self.scopes[-1].get_scope()

   ###########################################
   def add_scope(self, scope):
      self.scopes.append(scope)
      self.in_global = None

   ###########################################
   def back_to_parent(self):
      self.get_parent().in_global = True

   ###########################################
   def __is_ifmacro(self, line):
      return get_const_expr_of_if_preprocessor(line, \
         if_re, lambda m : m.group('const_expr'))

   ###########################################
   def __is_ifdef(self, line):
      return get_const_expr_of_if_preprocessor(line, \
         ifdef_re, lambda m : 'defined(' + m.group('macro') + ')')

   ###########################################
   def __is_ifndef(self, line):
      return get_const_expr_of_if_preprocessor(line, \
         ifndef_re, lambda m : '!defined(' + m.group('macro') + ')')

   ###########################################
   def is_cond_macro(self, line):
      const_expr = self.__is_ifmacro(line) or \
                   self.__is_ifdef(line) or \
                   self.__is_ifndef(line)

      if const_expr == None:
         return None

      self.add_scope(IfScope(self, const_expr))
      return True

##############################################

def fatal(msg):
   print >> sys.stderr, msg
   sys.exit(1)

##############################################

##############################################
class ConditionalScope(CompositeScope):
   def __init__(self, parent):
     CompositeScope.__init__(self, parent)
         
##############################################
zero_re   = re.compile( r'^0$' )
nz_dec_re = re.compile( r'^[^0][0-9]*$' )
nz_oct_re = re.compile( r'^0[0-7]+$' )
nz_hex_re = re.compile( r'^0[x|X][0-9A-Fa-f]+$' )
##############################################
class IfScope(ConditionalScope):

   ###########################################
   def __init__(self, parent, expr):
      ConditionalScope.__init__(self, parent)
      self.expr = expr

   ###########################################
   def get_expr(self):
      return self.expr

   ###########################################
   def matches_zero(self):
      return zero_re.match(self.expr) 

   ###########################################
   def matches_non_zero(self):
      return nz_dec_re.match(self.expr) or \
             nz_oct_re.match(self.expr) or \
             nz_hex_re.match(self.expr)

##############################################
def expecting_char(item, char, action_if_found):
   if not isinstance(item, Line):
      fatal("")
      
   line = item.get_content()
   for i in range(0, len(line)):
      if line[i] == char:
         action_if_found()
         return Line(line[i+1:])
      elif not line[i].isspace():
         fatal("")

   return Line("")

##############################################
class TestCase(CompositeScope):

   ###########################################
   def __init__(self, parent, name):
      CompositeScope.__init__(self, parent)
      self.name = name
      self.unmatched_braces = 0
      self.in_case = None

   ###########################################
   def found_start(self):
      self.unmatched_braces += 1
      self.in_case = True

   def __expecting_start(self, item):
      return expecting_char(item, "{", lambda : self.found_start())

   ###########################################
   def parse(self, item):
      pass

##############################################
id_pattern = '[A-Za-z_]\w*'

case_re = re.compile( r'^\s*void\s+(?P<name>' + \
                       id_pattern + \
                       ')\s*\((void)?\)(?P<rest>.*)$' )
##############################################
class TestFixture(CompositeScope):

   ###########################################
   def __init__(self, parent, name):
      CompositeScope.__init__(self, parent)
      self.name = name
      self.in_fixture = None
      self.leaving_fixture = None
      self.unmatched_braces = 0

   ###########################################
   def __found_start(self):
      self.in_fixture = True
      self.unmatched_braces += 1

   ###########################################
   def __expecting_start(self, item):
      return expecting_char(item, '{', lambda : self.__found_start())

   ###########################################
   def __found_end(self):
      self.leaving_fixture = None
      self.back_to_parent()

   ###########################################
   def __expecting_end(self, item):
      expecting_char(item, ';', lambda : self.__found_end())

   ###########################################
   def __skip_other_parts(self, content):
      for i in range(0, len(content)):
         if content[i] == '{':
            self.unmatched_braces += 1
         elif content[i] == '}':
            self.unmatched_braces -= 1
            if self.unmatched_braces == 0:
               self.in_fixture = None
               self.leaving_fixture = True
               return self.__expecting_end(Line(content[i+1:]))
            
   ###########################################
   def __handle_in_fixture(self, newline, item):
      if newline and self.is_cond_macro(item):
         return 

      if newline and self.unmatched_braces == 1:
         matched = case_re.match(item.get_content())
         if matched:
            self.add_scope(TestCase(self, matched.group("name")))
            self.get_scope().parse(Line(matched.group("rest")))
            return 

      self.__skip_other_parts(item.get_content())
         
   ###########################################
   def outside_fixture(self):
      return None

   ###########################################
   def inside_case(self):
      return get_scope().inside_case() 

   ###########################################
   def parse(self, item):
      if self.leaving_fixture:
         return self.__expecting_end(item)

      if self.in_fixture == None:
         rest = self.__expecting_start(item)
         if self.in_fixture:
            return self.__handle_in_fixture(None, rest)
        
      return self.__handle_in_fixture(True, item)

##############################################
id_pattern = "[A-Za-z_]\w*"

fixture_def_re = re.compile( r'^\s*(class|struct)\s+(?P<fixture>' + \
   id_pattern + ')\s*:\s*public\s+(?P<parent>((TESTCPP_NS|testcpp)\s*::\s*)?' + \
   id_pattern + ')(?P<rest>.*)$' )

predefined_fixturx_re = re.compile( r'TestFixture\w*' )
##############################################
class GlobalScope(CompositeScope):

   ###########################################
   def __init__(self):
      CompositeScope.__init__(self, None)
      self.has_fixture_tag = None
   
   ###########################################
   def __handle_tag(self, tag):
      if tag.get_tag() == "fixture":
         self.has_fixture_tag = True

   ###########################################
   def __validate_fixture(self, parent):
      if self.has_fixture_tag:
         return True

      return predefined_fixture_re.match(parent)
      
   ###########################################
   def __looking_for_fixture(self, content):
      matched = fixture_def_re.match(content)
      if matched and self.__validate_fixture(matched.group("parent")):
         self.add_scope(TestFixture(self, matched.group("fixture")))
         self.get_scope().parse(Line(matched.group("rest")))
         self.has_fixture_tag = None
         return
      
   ###########################################
   def outside_fixture(self):
      return True

   ###########################################
   def inside_case(self):
      return None

   ###########################################
   def parse(self, item):
      if isinstance(item, Tag):
         return self.__handle_tag(item)

      if self.is_cond_macro(item):
         return 

      return self.__looking_for_fixture(item.get_content())

##############################################
class Parser:

   ###########################################
   def __init__(self):
     self.global_scope = GlobalScope()
     self.line_parser = LineParser()

   ###########################################
   def get_scope(self):
     return self.global_scope

   ###########################################
   def parse(self, lines):
      for line in lines:
         if not isinstance(line, Comment) and \
            not isinstance(line, Continue):
            scope = self.global_scope.get_scope()
            item = self.line_parser.parse(line)
            scope.parse(item)
