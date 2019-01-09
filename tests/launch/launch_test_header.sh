#!/bin/bash

#-------------------------------------------------------------------------------
# Ce test compare la sortie parsé de readelf et de notre binaire (dobby_read_header) placé en argument.
#--------------------------------------------------------------------------------
dobby_bin=$1
output="output_$(date +%s)"

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

#---------------------Magique--------------------------------------
readelf -h $file_exemple | grep "Magique" >> file_out_elf
$dobby_bin $file_exemple | grep "Magique" >> file_out_prog

#------------------------------------------------------------------
#---------------------Classe--------------------------------------
readelf -h $file_exemple | grep "Classe" >> file_out_elf
$dobby_bin $file_exemple | grep "Classe" >> file_out_prog

#------------------------------------------------------------------
#---------------------Donnee--------------------------------------
donnees= readelf -h $file_exemple | grep "Données" | \
         cut --delimiter="(" --fields=2 | cut --delimiter=" " --fields=1 \
         &>/dev/null
donnees2= $dobby_bin $file_exemple | grep "Données" | \
          cut --delimiter=":" --fields=2 \
          &>/dev/null

if [ "${donnees,,}" != "${donnees2,,}" ]
then
  exit 1
fi
echo "Taille en-tête: $donnees" >> file_out_elf
echo "Taille en-tête: $donnees2" >> file_out_prog
#------------------------------------------------------------------
#---------------------Type--------------------------------------


type="$( readelf -h $file_exemple | grep "Type" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 )"

type2="$( $dobby_bin $file_exemple | grep "Type" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 )"

if [ -z $(echo $type | grep $type2) ]
then
  reussi="false"
  exit 1
fi
echo "Type: $type" >> file_out_elf
echo "Type: $type2" >> file_out_prog
#------------------------------------------------------------------
#---------------------Adresse--------------------------------------
readelf -h $file_exemple | grep "Adresse" >> file_out_elf
$dobby_bin $file_exemple | grep "Adresse" >> file_out_prog

#------------------------------------------------------------------
#---------------------Debut programme--------------------------------------
readelf -h $file_exemple | grep "Début des en-têtes du programme" >> file_out_elf
$dobby_bin $file_exemple | grep "Début des en-têtes du programme" >> file_out_prog

readelf -h $file_exemple | grep "Début des en-têtes de section" | cut --delimiter="(" --fields=1 >> file_out_elf
$dobby_bin $file_exemple | grep "Début des en-têtes de section" >> file_out_prog

#------------------------------------------------------------------
#---------------------Taille header--------------------------------------
taille="$( readelf -h $file_exemple | grep "Taille de cet en-tête" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 )"
taille2="$( $dobby_bin $file_exemple | grep "Taille de cet en-tête" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 )"
if [ -z $(echo $type | grep $type2) ]
then
  exit 1
fi
echo "Taille header: $taille" >> file_out_elf
echo "Taille header: $taille2" >> file_out_prog
#------------------------------------------------------------------
#---------------------Taille en-tete--------------------------------------
taille="$(readelf -h $file_exemple | grep "Taille de l'en-tête du programme" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 )"
taille2="$( $dobby_bin $file_exemple | grep "Taille de l'en-tête du programme" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 )"
if [ -z $(echo $type | grep $type2) ]
then
  exit 1
fi
echo "Taille en-tête: $taille" >> file_out_elf
echo "Taille en-tête: $taille2" >> file_out_prog
#------------------------------------------------------------------
#---------------------nombre d'entete prog--------------------------------------
readelf -h $file_exemple | grep "Nombre d'en-tête du programme" >> file_out_elf
$dobby_bin $file_exemple | grep "Nombre d'en-tête du programme" >> file_out_prog

readelf -h $file_exemple | grep "Début des en-têtes de section" | cut --delimiter="(" --fields=1 >> file_out_elf
$dobby_bin $file_exemple | grep "Début des en-têtes de section" >> file_out_prog

taille= readelf -h $file_exemple | grep "Taille des en-têtes de section:" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 \
      &>/dev/null
taille2= $dobby_bin $file_exemple | grep "Taille des en-têtes de section:" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 \
      &>/dev/null
echo "Taille section: $taille" >> file_out_elf
echo "Taille section: $taille2" >> file_out_prog
if [ -z $(echo $type | grep $type2) ]
then
  exit 1
fi

readelf -h $file_exemple | grep "Nombre d'en-têtes de section" >> file_out_elf
$dobby_bin $file_exemple | grep "Nombre d'en-têtes de section" >> file_out_prog
readelf -h $file_exemple | grep "Table d'indexes" >> file_out_elf
$dobby_bin $file_exemple | grep "Table d'indexes" >> file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  exit 1
fi
#------------------------------------------------------------------

exit 0
