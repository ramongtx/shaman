#!/bin/bash
SCRIPT_DIR=$(dirname ${BASH_SOURCE[0]})
for file in *.c 
do
	name=$(basename "$file")
	clang -cc1 -ast-dump $file | sed -n '/'"$name"'/,$p' >$file.ast
	$SCRIPT_DIR/ast2xml $file.ast > $file.xml
	echo "$name > $name.xml"
done