#!/usr/bin/python

class LogicalLine:
  def __init__(self, first_phys_line, line_number):
     self.line_number = line_number
     self.num_of_phys_lines = 0
     self.content = ""
    
     self.add_line(first_phys_line)

  def add_line(self, phys_line):
     self.content += self.remove_extra_heading_blanks(phys_line)
     self.num_of_phys_lines += 1
     if len(self.content) > 0:
        if self.content[-1] == "\\":
           self.content = self.content[:-2]

  def get_line_number(self):
     return self.line_number + self.num_of_phys_lines - 1

  def remove_extra_heading_blanks(self, phys_line):
     if len(phys_line) > 0 and phys_line[0] in [' ','/t','/n','/r']:
       return " " + phys_line.lstrip()

     return phys_line

  def get_content(self):
     return self.content
