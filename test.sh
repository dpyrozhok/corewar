i=39000
while [ $i -le 40000 ]
do
   echo $i;
  i=$(( i + 1000));
  ./corewar -dump $i $1 $2 $3 $4 > test1
  ./vm_champs/corewar -d $i $1 $2 $3 $4 > test2
  diff test1 test2;
done
