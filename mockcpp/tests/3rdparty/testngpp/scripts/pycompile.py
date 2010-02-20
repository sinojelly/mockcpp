#!/usr/bin/python

import py_compile
import compileall

py_compile.compile(r'testngppgen.py')
compileall.compile_dir(r'./testngppgen', 0)
