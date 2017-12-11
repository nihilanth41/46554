#!/bin/bash 
set -euf -o pipefail

i=0
while read line; do 
	i=$((i+1))
	cp -v -- "${line}" "detected_inputs/person_${i}.bmp"
done <detected.txt
	
