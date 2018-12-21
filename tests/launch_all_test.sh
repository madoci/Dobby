file_to_test=$1

if [ ! -f $file_to_test ] then
  echo "Fichier \"$file_to_test\" non existant"
  exit 1
fi

test_files=$(ls tests/$file_to_test.*.test)

if [ -z "$test_files" ] then
  echo "Aucun fichier test existant pour \"$file_to_test\""
  exit 1
fi

for file in $test_files
do
    ext_file=${file%.*}

    case "$ext_file" in
      ".h.test")
        #Do the header test
        ;;
      ".st.test")
      ;;
      ".sc.test")
      ;;
      ".rel.test")
      ;;
      ".sym.test")
      ;;
      *)
      ;;
done
