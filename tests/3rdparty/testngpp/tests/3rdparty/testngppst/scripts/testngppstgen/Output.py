
import os



################################################
def output2file(content, file):
   if file == None:
      return

   lines = content + "\n"
   try:
      file.writelines(lines)
   except:
      print "Some exception raised, maybe you tried to output some path with chinese or other non-ascii characters."
      raise

################################################
def output2null(content, file):
   return

################################################
output = output2file