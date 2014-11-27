#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")"; pwd)

printf "\n" > superindex.log
for folder in $(find . -maxdepth 1 -mindepth 1 -type d);
do
	echo "Indexing $folder"
	cd $folder
	VAR=$( ( $SCRIPT_DIR/all2xml.sh 1>shmindex.xml ) 2>&1 )
	printf "$VAR" > shmindex_log.txt
	cd ..

	if [ -z "$VAR" ]
	then
		printf "\tNo matches found\n"
	else
		NUM_LINES=$(echo "$VAR" | wc -l)
		printf "\t$NUM_LINES match(es) found\n"
		RESULT="$folder\n$VAR\n\n"
		printf "$RESULT" >> shmindex_log.txt
	fi
	#(cd $folder; $SCRIPT_DIR/all2xml.sh 2> shmindex.log)
done
