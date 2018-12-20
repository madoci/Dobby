dobby_bin=$1
output="output_$(date +%s)"
if [ ! -f $dobby_bin ]
then
  echo "Binaire \"$dobby_bin\" non existant"
  exit 1
fi
file=$2
file_test=$3

if [ ! -f $file_test ]
then
  echo "Fichier test \"$file_test\" non existant"
  exit 1
fi

file_out=$file_test.dobby
$dobby_bin $file > $file_out
diff -w -B --old-line-format="OBTENU  > (Ligne %3dn) %L" \
     --new-line-format="ATTENDU < (Ligne %3dn) %L" \
     --unchanged-line-format="" $file_out $file_test > $output
if [ ! -s $output ]
then
  echo -e "\033[7;40;1;5mResult of test : \"$file_test\" on command : ./$dobby_bin $file\033[0m : \033[32;1;5mTest réussi\033[0m\n"
else
  echo -e "\033[7;40;1;5mResult of test : \"$file_test\" on command : ./$dobby_bin $file\033[0m : \033[33;1;5mTest échoué\033[0m\n"
  cat $output
fi
rm $output
