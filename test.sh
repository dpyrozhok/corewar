i=0
while [ $i -le 250000 ]
do
   echo $i;
  i=$(( i + 101));
  ./corewar -dump $i turtle.cor > test1
  ./vm_champs/corewar -d $i turtle.cor > test2
  diff test1 test2;
done
