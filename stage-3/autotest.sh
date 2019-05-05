#!/bin/bash

#	Authors:
#		- Gabriel Pakulski da Silva - 00274701
#		- Lucas Sonntag Hagen       - 00274698

files="001 002 003 004 005 006 007 008 008 009 010"

make
rm -rf run
mkdir run
clear

echo
echo Iniciando testes
echo

for s in $files; do

    echo "TESTCASE_$s:"
    ./etapa3 < tests/TESTCASE_$s > run/T_1_$s
    ./etapa3 < run/T_1_$s > run/T_2_$s
    diff run/T_1_$s run/T_2_$s
    echo $?
    echo " - Done!"

done

rm -rf run

echo
echo Done ALL!
