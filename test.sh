i=0
while [ $i -le 10000 ]
do
   echo $i;
  i=$(( i + 8));
  ./corewar -dump $i zork.cor zork.cor zork.cor zork.cor > test1
  ./vm_champs/corewar -d $i zork.cor zork.cor zork.cor zork.cor > test2
  diff test1 test2;
done
