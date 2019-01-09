CC="arm-none-eabi-gcc -mbig-endian -mno-thumb-interwork -O0 "
CC_COMP="-c"
CC_S="-S"
CC_E="-nostdlib --entry main -n -Wl,--section-start -Wl,.text=0x20 -Wl,--section-start -Wl,.data=0x2800 -Wl,-EB"


#From C to arm assembly
for file in $(ls ARM_SOURCE/*.c)
do
  $CC $CC_S $file -o ARM_SOURCE/$(basename $file .c).s
done

#From arm assembly to obj
for file in $(ls ARM_SOURCE/*.s)
do
  $CC $CC_COMP $file -o ARM_OBJ/$(basename $file .s).o
done

#From obj to exec
for file in $(ls ARM_OBJ/*.o)
do
  $CC $CC_E $file -o ARM_BIN/$(basename $file .o)
done
