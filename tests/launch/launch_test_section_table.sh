#!/bin/bash
#-------------------------------------------------------------------------------
# Ce test compare la sortie parsé de readelf et de notre binaire (dobby-read-section-table) placé en argument.
#--------------------------------------------------------------------------------
dobby_bin=$1
output="output_"

if [ ! -f $dobby_bin ]
then
  echo "Binaire \"$dobby_bin\" non existant"
  exit 1
fi



file_exemple=$2
if [ ! -f $file_exemple ]
then
  echo "Exemple \"$file_exemple\" non existant"
  exit 1
fi

readelf -S $file_exemple | grep '[0-9]' > file_out_elf
$dobby_bin $file_exemple | grep '[0-9]' > file_out_prog

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
