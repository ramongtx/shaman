#!/bin/bash
find . -maxdepth 4 -type d -name 'subs' | while read path; do mv -v $path $(echo $path | sed 's/instaladas\///; s/\//-/g; s/-/\//'); done
find . -maxdepth 1 -mindepth 1 -type d -not -name '*-subs' -print0 | xargs -0 rm -rf