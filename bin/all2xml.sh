#!/bin/bash
SCRIPT_DIR=$(cd "$(dirname "$0")"; pwd)
hash clang 2>/dev/null || { echo >&2 "I require clang but it's not installed. Aborting."; exit 1; }
[ -f $SCRIPT_DIR/ast2xml ] || { echo >&2 "I require ast2xml but it's not installed. Aborting. Use make."; exit 1; }

FOLDER="*"
[ $# -eq 1 ] && FOLDER=$1
for file in $(find ${FOLDER} -name "*.c");
do
	name=$(basename "$file")
	clang -cc1 -ast-dump $file | sed -n '/'"$name"'/,$p' | $SCRIPT_DIR/ast2xml > $file.xml
	echo "$name > $name.xml"
done