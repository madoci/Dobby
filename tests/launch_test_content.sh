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



n=readelf -S $file_exemple | head -n 1 | cut --delimiter=" " --fields=4
for i in $(seq 0 $(($n-1)))
do
  readelf -x $n file_exemple | grep "0x" | cut --delimiter" " --fields=4-7 >> file_out_elf
done
for i in $(seq 0 $(($n-1)))
do
  $dobby_bin $file_exemple | grep '[0-9]' >> file_out_prog
done

diff --ignore-blank-lines --ignore-all-space \
--old-line-format='OBTENU  > (Ligne %3dn) %L' \
--new-line-format='ATTENDU < (Ligne %3dn) %L' \
--unchanged-line-format='' file_out_prog file_out_elf > $output

if [ -s $output ]
then
  reussi="false"
  echo "Content differente"
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
