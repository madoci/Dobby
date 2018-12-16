# Dobby
On voulait mettre un jeu de mot mais c'est tout de la daube 

##Pour compiler :
arm-eabi-gcc -mno-thumb-interwork fichier.c -o main
OU
arm-none-eabi-gcc idem

##Pour tester :
qemu-arm main