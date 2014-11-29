#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")"; pwd)
INDEX="$1"
if [ -z "$INDEX" ] ; then
	INDEX="shmindex_log.txt"
fi

echo "" > "$INDEX"
for folder in $(find . -maxdepth 1 -mindepth 1 -type d);
do
	echo "Indexing $folder"
	cd $folder
	VAR=$( ( $SCRIPT_DIR/all2xml.sh 1>shmindex.xml ) 2>&1 )
	printf "$VAR" > shmindex_log.txt
	cd ..

	NUM_LINES=$(echo "$VAR" | wc -l)
	NUM_LINES=$(($NUM_LINES-1))

	if [ "$NUM_LINES" -le "0" ]; then
		printf "\tNo matches found\n"
	else
		NUM_LINES=$(echo "$VAR" | wc -l)
		NUM_LINES=$(($NUM_LINES-1))
		printf "\t$NUM_LINES match(es) found\n"
		RESULT="$folder    $VAR\n\n"
		printf "$RESULT" >>  "$INDEX"
	fi
	#(cd $folder; $SCRIPT_DIR/all2xml.sh 2> shmindex.log)
done