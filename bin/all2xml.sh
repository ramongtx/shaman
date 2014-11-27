#!/bin/bash
SCRIPT_DIR=$(cd "$(dirname "$0")"; pwd)
hash clang 2>/dev/null || { echo >&2 "I require clang but it's not installed. Aborting."; exit 1; }
[ -f $SCRIPT_DIR/ast2xml ] || { echo >&2 "I require ast2xml but it's not installed. Aborting. Use make."; exit 1; }
[ -f $SCRIPT_DIR/xml2index ] || { echo >&2 "I require xml2index but it's not installed. Aborting. Use make."; exit 1; }

xmls=""
FOLDER="*"
## [ $# -eq 1 ] && FOLDER=$1
for file in $(find ${FOLDER} -name "*.c");
do
	name=$(basename "$file")
	dirname=$(dirname "$file")
	outputFile="$dirname/check__codes__"
	compoundName=$(echo $file | tr "/" "-")
	if [ ! -f $compoundName.xml ]; then
		clang -cc1 -ast-dump $file | sed -n '/'"$name"'/,$p' | $SCRIPT_DIR/ast2xml > $compoundName.xml 2>&1
	fi
	## clang -cc1 -ast-dump $file | $SCRIPT_DIR/ast2xml > $compoundName.xml
	echo "$file > $compoundName.xml"
	xmls+=" $compoundName.xml"
	xmls+=" $outputFile"
done

echo "xml2index $xmls"
$SCRIPT_DIR/xml2index $xmls > shmindex.xml