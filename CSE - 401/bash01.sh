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

#git add . && git commit -m "Update of bash scripting" && git push

:<<COMMENT
get_name() {
	echo "John"
}
echo "You are $(get_name)"
COMMENT

:<<COMMENT
string="abir"

if [[ -z "$string" ]]; then
	echo "String is empty"
elif [[ -n "$string" ]]; then
	echo "String is not empty"
fi
COMMENT

:<<COMMENT
echo {A,B}hello
echo {1..10}
echo {{1..3},{7..9}}
COMMENT

:<<COMMENT
name="John"
echo "${name}"
echo "${name/J/j}" #substitution 'J' with 'j'
echo "${name:0:2}" #slicing
echo "${name::2}" #slicing
echo "${name::-1}" #slicing
echo "${name:(-1)}" #slicing from right
echo "${name:(-2):1}" #slicing from right
echo "${food:-Cake}" # $food or "Cake"

length=2
echo "${name:0:length}"
COMMENT

:<<COMMENT
str="/path/to/foo.cpp"
echo "${str%.cpp}"
echo "${str%.cpp}.o"
echo "${str%/*}"

echo "${str##*.}"
echo "${str##*/}"

echo "${str#*/}"
echo "${str#*/*/}"

echo "${str/foo/bar}"
COMMENT

:<<COMMENT
str="Hello world"
echo "${str:6:5}"
echo "${str: -5:5}"

src="/path/to/foo.cpp"
base=${src##*/}
dir=${src%$base}

echo "${base}"
echo "${dir}"
COMMENT

:<<comment
foo="a/b/c/d/e"
suf="d/e"
pre="a/b"

echo "${foo%/*}"
echo "${foo%%/*}"
echo "${foo%/*/*}"
echo "${foo%$suf}"
echo "${foo#*/}"
echo "${foo##*/}"
comment

:<<comment
str="Hello World"
echo "${#str}"

value="HELLO WORLD"
echo "${value,}"
echo "${value,,}"

value="hello world"
echo "${value^}"
echo "${value^^}"
comment

#foo="That"
#val="This"
#echo "${foo:-$val}" #show foo or val if foo is unset
#echo "${foo:=$val}" #set foo to val if unset
#echo "${foo:+$val}" # val if foo is set
#echo "${foo:?message}" #show error message and exit if foo is unset

:<<comment
for ((i = 0; i < 100; i++)); do
	echo "$i"
done

for i in {1..5}; do
	echo "$i"
done

for i in {0..25..5}; do
	echo "$i"
done
comment

while read -r line; do
	echo "$line"
done <bashLine.txt
