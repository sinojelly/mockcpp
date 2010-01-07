#!/usr/bin/python

from testcppgen2 import *

import unittest

#####################################################################
class TagsParserTestCase(unittest.TestCase):
   def test_should_be_able_to_recogonize_slc_for_tag_def(self):
      line = "  // @tag : abc def "
      parser = TagParser()
      content = parser.parse(line)
      assert content.get_tag() == "tag"
      assert content.get_value() == "abc def"

   def test_should_be_able_to_recoginize_slc_tag_without_value(self):
      line = "  // @tag "
      parser = TagParser()
      content = parser.parse(line)
      assert content.get_tag() == "tag"
      assert content.get_value() == None

   def test_should_be_able_to_recoginize_slc_tag_with_empty_value(self):
      line = "  // @ tag : "
      parser = TagParser()
      content = parser.parse(line)
      assert content.get_tag() == "tag"
      assert content.get_value() == ""

#####################################################################
class LineParserTestCase(unittest.TestCase):
   def test_should_be_able_to_recogonize_multi_line_comments_in_single_line(self):
      line = "const char* /* this is a mlc in single line */ chr /**/ ;"
      parser = LineParser()
      result = parser.parse(line)
      assert isinstance(result, Line)
      assert result.get_content() == "const char*  chr  ;"

   def test_should_be_able_to_recognize_multi_line_comments_in_multi_line(self):
      line = "const char* chr/* this is a mlc */; /*single line chr "
      parser = LineParser()
      result = parser.parse(line)
      assert isinstance(result, Line)
      assert result.get_content() == "const char* chr; "

   def test_should_be_able_to_recognize_the_fully_commented_line(self):
      line = "/* const char* chr; */"
      parser = LineParser()

      result = parser.parse(line)
      assert isinstance(result, Line)
      assert result.get_content() == ""

   def test_should_be_able_to_recognize_end_of_multi_line_comments_in_multi_line(self):
      line0 = "const char* chr/* this is a mlc */; /*single line chr "
      line1 = "const char* chr;"
      line2 = "const char* chr/* this is a mlc */ void func()/* */; "

      parser = LineParser()

      parser.parse(line0)

      result = parser.parse(line1)
      assert isinstance(result, Comment)

      result = parser.parse(line2)
      assert isinstance(result, Line)
      assert result.get_content() == " void func(); "
      
   def test_should_be_able_recognize_single_line_comment(self):
      line = "const char* /* mlc */ chr; // slc ; */"
      parser = LineParser()

      result = parser.parse(line)
      assert isinstance(result, Line)
      assert result.get_content() == "const char*  chr; "


   def test_should_be_able_recognize_mlc_containing_slc_symbol(self):
      line = "const char* /* mlc  chr; // slc ; */"
      parser = LineParser()

      result = parser.parse(line)
      assert isinstance(result, Line)
      assert result.get_content() == "const char* "

   def test_should_be_able_to_recognize_line_feed(self):
      line0 = "const char* \\"
      line1 = "chr\\"
      line2 = ";"

      parser = LineParser()

      result = parser.parse(line0)
      assert isinstance(result, Continue)

      result = parser.parse(line1)
      assert isinstance(result, Continue)

      result = parser.parse(line2)
      assert isinstance(result, Line)
      assert result.get_content() == "const char* chr;"

   def test_should_be_able_to_recognize_line_feed_in_comments(self):
      line0 = "const char* // \\"
      line1 = "chr\\"
      line2 = ";"

      parser = LineParser()

      result = parser.parse(line0)
      assert isinstance(result, Continue)

      result = parser.parse(line1)
      assert isinstance(result, Continue)

      result = parser.parse(line2)
      assert isinstance(result, Line)
      assert result.get_content() == "const char* "

   def test_should_be_able_to_regonize_tag_def(self):
      line = " // @ tag : value "
      parser = LineParser()
      result = parser.parse(line)
      assert isinstance(result, Tag)
      assert result.get_tag() == "tag"
      assert result.get_value() == "value"
      
class CompositeScopeTestCase(unittest.TestCase):
   def test_should_be_able_to_recogize_if_macros(self):
      line = Line(" # if WHATEVER && STHELSE ")
      scope = CompositeScope(None)
      assert scope.is_cond_macro(line)
      assert isinstance(scope.get_scope(), IfScope)
      assert scope.get_scope().get_expr() == "WHATEVER && STHELSE"

   def test_should_be_able_to_recognize_ifdef(self):
      line = Line(" # ifdef WHATEVER ")
      scope = CompositeScope(None)
      assert scope.is_cond_macro(line)
      assert isinstance(scope.get_scope(), IfScope)
      assert scope.get_scope().get_expr() == "defined(WHATEVER)"
      
   def test_should_be_able_to_recognize_ifndef(self):
      line = Line(" # ifndef WHATEVER ")
      scope = CompositeScope(None)
      assert scope.is_cond_macro(line)
      assert isinstance(scope.get_scope(), IfScope)
      assert scope.get_scope().get_expr() == "!defined(WHATEVER)"
      
#####################################################################
class ParserTestCase(unittest.TestCase):
   def test_should_be_able_to_recognize_test_fixture(self):
      lines = [" // @ fixture ", " struct MyTestFixture : public Reusable { /* */" ]
      parser = Parser()

      parser.parse(lines)
      assert isinstance(parser.get_scope().get_scope(), TestFixture)

   def test_should_be_able_to_recognize_end_of_test_fixture_in_same_line(self):
      lines = [" // @ fixture ", " struct MyTestFixture : public Reusable { /* */ };" ]
      parser = Parser()

      parser.parse(lines)
      assert isinstance(parser.get_scope().get_scope(), GlobalScope)

   def test_should_be_able_to_recognize_end_of_test_fixture_in_different_line(self):
      lines = [" // @ fixture ", " struct MyTestFixture : public Reusable {", "/* */ };" ]
      parser = Parser()

      parser.parse(lines)

   def test_should_be_able_to_recognize_end_of_test_fixture_in_different_lines(self):
      lines = [" // @ fixture ", " struct MyTestFixture : public Reusable {", "/* */ }", ";" ]
      parser = Parser()

      parser.parse(lines)

#####################################################################
if __name__ == '__main__':
   unittest.main()

