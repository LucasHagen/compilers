#!/bin/bash

#	Authors:
#		- Gabriel Pakulski da Silva - 00274701
#		- Lucas Sonntag Hagen       - 00274698

files="001 002 003 004 005 006 007 008 008 009 010"

make > /dev/null
rm -rf run
mkdir run

echo
echo "Starting Tests..."
echo

for s in $files; do

    ./etapa3 < tests/TESTCASE_$s > run/T_1_$s
    ./etapa3 < run/T_1_$s > run/T_2_$s
    diff run/T_1_$s run/T_2_$s > /dev/null
    echo "TESTCASE_$s: $?"

done

rm -rf run

echo
echo "0 = SUCCESS"
echo "1 = FAIL"
echo
echo "Finished tests"
