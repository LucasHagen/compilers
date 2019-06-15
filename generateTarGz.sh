#!/bin/bash

#	Authors:
#		- Gabriel Pakulski da Silva - 00274701
#		- Lucas Sonntag Hagen       - 00274698

stages="1 2 3 4 5 6"

echo
echo Gerando TGZs...
echo

for s in $stages; do

    echo "Etapa $s:"
    cd stage-$s
    make clean > /dev/null
    tar czf ../etapa$s.tgz *
    cd ..
    echo " - Done!"

done

echo
echo Done ALL!
