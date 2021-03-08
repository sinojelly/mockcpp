#!/bin/bash

all_headers=`find ./src ./include ./samples -name *.h*`
all_srcs=`find ./src -name *.c*`
all_makes=`find . -name CMakeLists.txt`
all_scripts=`find ./scripts -name *.py`
all_files="${all_headers} ${all_srcs} ${all_scripts} ${all_makes}"

temp_suffix=.temp
for file in ${all_files}; do
   sed s/TESTNGPP/TESTNGPPST/g < ${file} > ${file}.${temp_suffix}
   sed s/testngpp/testngppst/g < ${file}.${temp_suffix} > ${file}
   rm -f ${file}.${temp_suffix}
done

mv include/testngpp/testngpp.h include/testngpp/testngppst.h
mv include/testngpp/testngpp.hpp include/testngpp/testngppst.hpp
mv include/testngpp include/testngppst
mv scripts/testngppgen scripts/testngppstgen
mv scripts/testngppgen.py scripts/testngppstgen.py
