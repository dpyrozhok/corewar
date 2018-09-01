i=0
while [ $i -le 250000 ]
do
   echo $i;
  i=$(( i + 101));
  ./corewar -dump $i fluttershy.cor > test1
  ./vm_champs/corewar -d $i fluttershy.cor > test2
  diff test1 test2;
done
