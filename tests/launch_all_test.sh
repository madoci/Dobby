

liste_bin=$(find ARM_BIN -type f)
liste_obj=$(find ARM_OBJ -type f)
log=$(date +%H-%M-%S_%d-%m)

echo -e "\nHeader : "
for file in $liste_bin $liste_obj
do
  rm -f output* file_out*
  ./launch/launch_test_header.sh ../bin/dobby-read-header $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur $file"
  else
    echo "OK."
  fi

  #log-------------------------------
  echo "Header:" >> ./logs/$log
  echo "$file" >> ./logs/$log
  diff -y ./file_out* >> ./logs/$log
  if [ -f ./output* ]
  then
    cat ./output* >> ./logs/$log
  fi
  echo -e "\n\n" >> ./logs/$log
  #----------------------------------
done


echo -e "\nSection table :"
for file in $liste_bin $liste_obj
do
  rm -f ./output* ./file_out*
  ./launch/launch_test_section_table.sh ../bin/dobby-read-section-table $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur $file"
  else
    echo "OK."
  fi
  #log-------------------------------
  echo "Section Table:" >> ./logs/$log
  echo "$file" >> ./logs/$log
  diff -y ./file_out* >> ./logs/$log
  if [ -f ./output* ]
  then
    cat ./output* >> ./logs/$log
  fi
  echo -e "\n\n" >> ./logs/$log
  #----------------------------------
done

echo -e "\nSection content"
for file in $liste_bin $liste_obj
do
  rm -f ./output* ./file_out*
  ./launch/launch_test_section_content.sh ../bin/dobby-read-section-content $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur: $file"
  else
    echo "OK."
  fi
  #log-------------------------------
  echo "Section Content:" >> ./logs/$log
  echo "$file" >> ./logs/$log
  diff -y ./file_out* >> ./logs/$log
  if [ -f ./output* ]
  then
    cat ./output* >> ./logs/$log
  fi
  echo -e "\n\n" >> ./logs/$log
  #----------------------------------
done

echo -e "\nRelocs : "
for file in $liste_obj
do
  rm -f ./output* ./file_out*
  ./launch/launch_test_reloc.sh ../bin/dobby-read-relocation-table $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur $file"
  else
    echo "OK."
  fi
  #log-------------------------------
  echo "Reloc:" >> ./logs/$log
  echo "$file" >> ./logs/$log
  diff -y ./file_out* >> ./logs/$log
  if [ -f ./output* ]
  then
    cat ./output* >> ./logs/$log
  fi
  echo -e "\n\n" >> ./logs/$log
  #----------------------------------
done

echo -e "\nSymbole"
for file in $liste_obj
do
  rm -f ./output* ./file_out*
  ./launch/launch_test_symbole.sh ../bin/dobby-read-symbol-table $file
  if [ $? -eq 1 ]
  then
    echo "test echoué sur $file"
  else
    echo "OK."
  fi
  #log-------------------------------
  echo "Symbole:" >> ./logs/$log
  echo "$file" >> ./logs/$log
  diff -y ./file_out* >> ./logs/$log
  if [ -f ./output* ]
  then
    cat ./output* >> ./logs/$log
  fi
  echo -e "\n\n" >> ./logs/$log
  #----------------------------------
done
rm -f ./output* ./file_out*
