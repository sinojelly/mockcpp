#!/usr/bin/python

import sys
import os.path
from get_long_opt import *

delegatedMethodGetDefFileName = "DelegatedMethodGetDef.h"
delegatedMethodGetByVptrDefFileName = "DelegatedMethodGetByVptrDef.h"
destructorCheckerDefFileName = "DestructorCheckerDef.h"
genericMethodCheckerDefFileName = "GenericMethodCheckerDef.h"
destructorGetterDefFileName = "DestructorAddrGetterDef.h"
defaultMethodGetterDefFileName = "DefaultMethodAddrGetterDef.h"

allowMIOpt          = LongOptString("allow-mi", "yes")
maxInheritanceOpt   = LongOptString("max-inheritance", "2")
maxVtblSizeOpt      = LongOptString("max-vtbl-size", "10")
includePathOpt      = LongOptString("include-path", "/home/darwin/mockcpp/include")

longOpts = [ allowMIOpt
           , maxInheritanceOpt
           , maxVtblSizeOpt
           , includePathOpt]

def getGenericMethodCheckerDefContent(maxInheritance, maxVtblSize):
   lineStr = '''MOCKCPP_SET_GENERIC_METHOD_CHECKER_VTBL(%d, %d);'''
   lines = []
   for i in range(0, maxInheritance):
      for j in range(0, maxVtblSize):
         lines.append(lineStr % (i,j))

   return getContent(lines)

def generateGenericMethodCheckerDef(includePath, maxInheritance, maxVtblSize):
   content = getGenericMethodCheckerDefContent(maxInheritance, maxVtblSize)
   writeFile(includePath + "/" + genericMethodCheckerDefFileName, content)

def getDestructorAddrGetterDefContent(maxInheritance):
   lineStr = '''MOCKCPP_GET_DESTRUCTOR_ADDR(%d)'''
   lines = []
   for i in range(0, maxInheritance):
      lines.append(lineStr % i)

   return getContent(lines)

def generateDestructorAddrGetterDef(includePath, maxInheritance):
   content = getDestructorAddrGetterDefContent(maxInheritance)
   writeFile(includePath + "/" + destructorGetterDefFileName, content)

def getDestructorCheckerDefContent(maxInheritance, maxVtblSize):
   lineStr = '''MOCKCPP_SET_DESTRUCTOR_CHECKER_VTBL(%d, %d);'''
   lines = []
   for i in range(0, maxInheritance):
      for j in range(0, maxVtblSize):
         lines.append(lineStr % (i,j))

   return getContent(lines)

def generateDestructorCheckerDef(includePath, maxInheritance, maxVtblSize):
   content = getDestructorCheckerDefContent(maxInheritance, maxVtblSize)
   writeFile(includePath + "/" + destructorCheckerDefFileName, content)

def getDefaultMethodAddrGetterDefContent(maxInheritance, maxVtblSize):
   lineStr = '''MOCKCPP_SET_DEFAULT_METHOD(%d, %d);'''
   lines = []
   for i in range(0, maxInheritance):
      for j in range(0, maxVtblSize):
         lines.append(lineStr % (i,j))

   return getContent(lines)

def generateDefaultMethodAddrGetterDef(includePath, maxInheritance, maxVtblSize):
   content = getDefaultMethodAddrGetterDefContent(maxInheritance, maxVtblSize)
   writeFile(includePath + "/" + defaultMethodGetterDefFileName, content)

def getDelegatedMethodGetDefContent(maxVtblSize):
   lineStr = '''DELEGATED_METHOD_GET(VPTRIndex, %d)'''
   lines = []
   for i in range(0, maxVtblSize):
      lines.append(lineStr % i)

   return getContent(lines)

def generateDelegatedMethodGetDef(includePath, maxVtblSize):
   content = getDelegatedMethodGetDefContent(maxVtblSize)
   writeFile(includePath + "/" + delegatedMethodGetDefFileName, content)

def getDelegatedMethodGetByVptrDefContent(maxInheritance):
   lineStr = '''DELEGATED_METHOD_GET_BY_VPTR(%d, vtblIndex)'''
   lines = []
   for i in range(0, maxInheritance):
      lines.append(lineStr % i)

   return getContent(lines)

def generateDelegatedMethodGetByIndexDef(includePath, maxInheritance):
   content = getDelegatedMethodGetByVptrDefContent(maxInheritance)
   writeFile(includePath + "/" + delegatedMethodGetByVptrDefFileName, content)

def writeFile(name, content):
   FILE = open(name, "w")
   FILE.writelines(content)
   FILE.close()

def main():
   optlist, args = getOpt(longOpts)

   allowMI = None
   maxInheritance = 2
   maxVtblSize = 20
   includePath = "."

   for o, a in optlist:
      if o == allowMIOpt.toLongOptString():
         if a == "yes":
            allowMI = True 
      if o == maxInheritanceOpt.toLongOptString():
         maxInheritance = int(a)
      if o == maxVtblSizeOpt.toLongOptString():
         maxVtblSize = int(a)
      if o == includePathOpt.toLongOptString():
         includePath = a

   if delegatedMethodGetDefFileName in args:
      generateDelegatedMethodGetDef(includePath, maxVtblSize)

   if not allowMI:
     maxInheritance = 1

   if delegatedMethodGetByVptrDefFileName in args:
      generateDelegatedMethodGetByIndexDef(includePath, maxInheritance)

   if destructorCheckerDefFileName in args:
      generateDestructorCheckerDef(includePath, maxInheritance, maxVtblSize)

   if destructorGetterDefFileName in args:
      generateDestructorAddrGetterDef(includePath, maxInheritance)
     
   if genericMethodCheckerDefFileName in args:
      generateGenericMethodCheckerDef(includePath, maxInheritance, maxVtblSize)

   if defaultMethodGetterDefFileName in args:
      generateDefaultMethodAddrGetterDef(includePath, maxInheritance, maxVtblSize)

if __name__ == "__main__":
    main()
