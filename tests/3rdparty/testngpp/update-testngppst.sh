#!/bin/bash

DEST_DIR="tests/3rdparty/testngppst2"
mkdir -p $DEST_DIR

function copyDir() {
	#mkdir -p $DEST_DIR/$1
	#cp -r $1 $DEST_DIR
	svn export $1 $DEST_DIR/$1
}

function copyFile() {
	cp $1 $DEST_DIR
}

copyDir include
svn export 3rdparty/mem_checker $DEST_DIR/include/mem_checker

copyDir src
copyDir scripts

copyFile CMakeLists.txt
copyFile ProjectVar.txt
copyFile change-name.sh

cd $DEST_DIR
./change-name.sh
rm change-name.sh

cd ..
rm -rf testngppst
mv testngppst2 testngppst

