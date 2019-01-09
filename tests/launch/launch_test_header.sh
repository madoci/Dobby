#!/bin/bash

#-------------------------------------------------------------------------------
# Ce test compare la sortie parsé de readelf et de notre binaire (dobby_read_header) placé en argument.
#--------------------------------------------------------------------------------
dobby_bin=$1


if [ ! -f $dobby_bin ]
then
  echo "Binaire \"$dobby_bin\" non existant"
  exit 1
fi

output="output_$(date +%s)"

file_exemple=$2
if [ ! -f $file_exemple ]
then
  echo "Exemple \"$file_exemple\" non existant"
  exit 1
fi

#---------------------Magique--------------------------------------
readelf -h $file_exemple | grep "Magique" > file_out_elf
$dobby_bin $file_exemple | grep "Magique" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output

if [ -s $output ]
then
  exit 1
fi
#------------------------------------------------------------------
#---------------------Classe--------------------------------------
readelf -h $file_exemple | grep "Classe" > file_out_elf
$dobby_bin $file_exemple | grep "Classe" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  exit 1
fi
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
#------------------------------------------------------------------
#---------------------Adresse--------------------------------------
readelf -h $file_exemple | grep "Adresse" > file_out_elf
$dobby_bin $file_exemple | grep "Adresse" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  echo -e "Adresse d'entrée differente sur $file_exemple avec $dobby_bin \n"
  exit 1
fi
#------------------------------------------------------------------
#---------------------Debut programme--------------------------------------
readelf -h $file_exemple | grep "Début des en-têtes du programme" > file_out_elf

$dobby_bin $file_exemple | grep "Début des en-têtes du programme" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  exit 1
fi
#------------------------------------------------------------------
#---------------------Debut section--------------------------------------
readelf -h $file_exemple | grep "Début des en-têtes de section" | cut --delimiter="(" --fields=1 > file_out_elf
$dobby_bin $file_exemple | grep "Début des en-têtes de section" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  exit 1
fi
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
#------------------------------------------------------------------
#---------------------nombre d'entete prog--------------------------------------
readelf -h $file_exemple | grep "Nombre d'en-tête du programme" > file_out_elf
$dobby_bin $file_exemple | grep "Nombre d'en-tête du programme" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  exit 1
fi
#------------------------------------------------------------------
#---------------------Debut section--------------------------------------
readelf -h $file_exemple | grep "Début des en-têtes de section" | cut --delimiter="(" --fields=1 > file_out_elf
$dobby_bin $file_exemple | grep "Début des en-têtes de section" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  exit 1
fi
#------------------------------------------------------------------
#---------------------Taille en-tete section--------------------------------------
taille= readelf -h $file_exemple | grep "Taille des en-têtes de section:" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 \
      &>/dev/null
taille2= $dobby_bin $file_exemple | grep "Taille des en-têtes de section:" | \
      cut --delimiter=":" --fields=2 | cut --delimiter="(" --fields=1 \
      &>/dev/null
if [ -z $(echo $type | grep $type2) ]
then
  exit 1
fi
#------------------------------------------------------------------

#---------------------Nombre d'entete section--------------------------------------
readelf -h $file_exemple | grep "Nombre d'en-têtes de section" > file_out_elf
$dobby_bin $file_exemple | grep "Nombre d'en-têtes de section" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  exit 1
fi
#------------------------------------------------------------------
#---------------------Table indexe--------------------------------------
readelf -h $file_exemple | grep "Table d'indexes" > file_out_elf
$dobby_bin $file_exemple | grep "Table d'indexes" > file_out_prog

diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" file_out_prog file_out_elf > $output
if [ -s $output ]
then
  exit 1
fi
#------------------------------------------------------------------
rm $output file_out_elf file_out_prog
exit 0
