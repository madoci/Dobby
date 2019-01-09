

liste_dobby=$(find ../bin/ -type f)
example_liste_OBJ=$(find ARM_BIN -type f)
example_liste_BIN=$(find ARM_OBJ -type f)
log=valgrind_$(date +%H-%M-%S_%d-%m)
output=output_

for dobby_bin in $liste_dobby
do
  echo "$dobby_bin : "
  for example in $example_liste_BIN $example_liste_OBJ
  do

    result="$(valgrind $dobby_bin $example 2>&1 > /dev/null | head -n -3 | tail -n +7)"
    echo $result | grep "no leaks are possible" > $output
    echo -e "$dobby_bin $example : \n $result\n\n\n" >> ./logs/$log
    if [ ! -s $output ]
    then
      echo "Echoué sur $example"
    else
      echo "OK"
    fi
  done
done

rm -f $output
