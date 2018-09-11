i=1
while [ $i -le 50000 ]
do
   echo $i;
  i=$(( i + 11));
  ./corewar -dump $i $1 $2 $3 $4 > test1
  ./vm_champs/corewar -d $i $1 $2 $3 $4 > test2
  diff test1 test2;
done
