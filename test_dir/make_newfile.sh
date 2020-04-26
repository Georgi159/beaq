#!/bin/sh

echo "OLD FILE"
cat updatefile.txt
date > updatefile.txt
echo "\nNEW FILE"
cat updatefile.txt
