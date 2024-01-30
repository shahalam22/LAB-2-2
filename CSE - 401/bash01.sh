#!/usr/bin/env bash

:<<COMMENT
name="John"
echo $name
echo "$name"
echo "${name}!"
COMMENT

:<<COMMENT
wildcard="*.txt"
options="iv"
cp -$options $wildcard temp
COMMENT

:<<COMMENT
name="John"
echo "Hi $name"
echo 'Hi $name'
COMMENT

:<<COMMENT
echo "I'm in $(pwd)"
echo "I'm in `pwd`"
COMMENT

:<<COMMENT
git commit && git push
git commit || echo "Commit Failed"
COMMENT

git add . && git commit -m "Update of bash scripting" && git push
