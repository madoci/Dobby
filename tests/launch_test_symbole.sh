#!/bin/bash

dobby_bin=$1
reussi="true"

if [ $# -ne 2 ]
then
  echo "Argument manquant"
  exit 1
fi

if [ ! -f $dobby_bin ]
then
  echo "Binaire \"$dobby_bin\" non existant"
  exit 1
fi

output="output_"
echo "TEST" > $output

file_exemple=$2
if [ ! -f $file_exemple ]
then
  echo "Exemple \"$file_exemple\" non existant"
  exit 1
fi


readelf -s $file_exemple | grep '[0-9]:' > file_out_elf
$dobby_bin $file_exemple | grep '[0-9]:' > file_out_prog

diff --ignore-blank-lines --ignore-all-space \
--old-line-format='OBTENU  > (Ligne %3dn) %L' \
--new-line-format='ATTENDU < (Ligne %3dn) %L' \
--unchanged-line-format='' file_out_prog file_out_elf > $output

if [ -s $output ]
then
  reussi="false"
  echo "Table section differente"
  echo -e "$(cat $output) \n EOF"
fi
#------------------------------------------------------------------

if [ "$reussi" = "true" ]
  then
    echo -e "Test Reussi"
  else
    echo "Test Echoué"
fi
#rm $output file_out*
