#!/bin/bash
#-------------------------------------------------------------------------------
# Ce test compare la sortie parsé de readelf et de notre binaire (dobby-read-section-content) placé en argument.
#--------------------------------------------------------------------------------
dobby_bin=$1
nom=$3

rm -f $output file_out*

if [ $# -lt 2 ] || [ $# -gt 3 ]
then
  echo "Argument invalide"
  exit 1
fi

if [ ! -f $dobby_bin ]
then
  echo "Binaire \"$dobby_bin\" non existant"
  exit 1
fi

output="output_"


file_exemple=$2
if [ ! -f $file_exemple ]
then
  echo "Exemple \"$file_exemple\" non existant"
  exit 1
fi


if [ $# -eq 2 ]
then
  n=$(readelf -S $file_exemple | head -n 1 | cut --delimiter=" " --fields=4)
  for i in $(seq 0 $(($n-1)))
  do
    readelf -x $i $file_exemple | grep "0x" | cut --delimiter=" " --fields=4-7 >> file_out_elf
    $dobby_bin $file_exemple -i $i | grep '[0-9]' >> file_out_prog
  done

else
  readelf -x $nom $file_exemple | grep "0x" | cut --delimiter=" " --fields=4-7 >> file_out_elf
  $dobby_bin $file_exemple -s $nom | grep '[0-9]' > file_out_prog
fi

diff --ignore-blank-lines --ignore-all-space \
--old-line-format='OBTENU  > (Ligne %3dn) %L' \
--new-line-format='ATTENDU < (Ligne %3dn) %L' \
--unchanged-line-format='' file_out_prog file_out_elf > $output

if [ -s $output ]
then
  exit 1
fi
#------------------------------------------------------------------

exit 0
rm $output file_out*
