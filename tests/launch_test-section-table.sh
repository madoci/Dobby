dobby_bin="../bin/dobby-read-section-table"
output="output_$(date +%s)"
if [ ! -f $dobby_bin ]
then
  echo "Binaire \"$dobby_bin\" non existant"
  exit 1
fi
file=$1
#file_test=$2

if [ ! -f $file ]
then
  echo "Fichier \"$file\" non existant"
  exit 1
fi

file_test=$file.readelf
file_out=$file.dobby
$dobby_bin $file > $file_out
readelf -S $file > $file_test
diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" $file_out $file_test > $output
if [ ! -s $output ]
then
  echo -e "\033[7;40mResult of test :  ./$dobby_bin $file\033[0m : \033[32mTest réussi\033[0m\n"
else
  echo -e "\033[7;40mResult of test :  ./$dobby_bin $file\033[0m : \033[33mTest échoué\033[0m\n"
  cat $output
fi
rm $output
rm $file_test
rm $file_out
