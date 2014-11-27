#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")"; pwd)

for folder in $(find . -maxdepth 1 -mindepth 1 -type d);
do
	echo "----- $folder"
	(cd $folder; $SCRIPT_DIR/all2xml.sh 2> log.log)
done
