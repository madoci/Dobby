

liste_bin=$(find ARM_BIN -type f)
liste_obj=$(find ARM_OBJ -type f)

echo -e "\nHeader : "
for file in $liste_bin $liste_obj
do
  ./launch/launch_test_header.sh ../bin/dobby-read-header $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur $file"
  else
    echo "OK."
  fi
done

echo -e "\nSection table :"
for file in $liste_bin $liste_obj
do
  ./launch/launch_test_section_table.sh ../bin/dobby-read-section-table $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur $file"
  else
    echo "OK."
  fi
done

echo -e "\nSection content"
for file in $liste_bin $liste_obj
do
  ./launch/launch_test_section_content.sh ../bin/dobby-read-section-content $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur: $file"
  else
    echo "OK."
  fi
done

echo -e "\nRelocs : "
for file in $liste_obj
do
  ./launch/launch_test_reloc.sh ../bin/dobby-read-relocation-table $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur $file"
  else
    echo "OK."
  fi
done

echo -e "\nSymbole"
for file in $liste_obj
do
  ./launch/launch_test_symbole.sh ../bin/dobby-read-symbol-table $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur $file"
  else
    echo "OK."
  fi
done
