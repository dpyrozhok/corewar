i=0
while [ $i -le 300000 ]
do
   echo $i;
  i=$(( i + 101));
  ./corewar -dump $i $1 $2 $3 $4 > test1
  ./vm_champs/corewar -d $i $1 $2 $3 $4 > test2
  diff test1 test2;
done
