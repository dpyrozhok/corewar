i=1600
while [ $i -le 20000 ]
do
   echo $i;
  i=$(( i + 1));
  ./corewar -dump $i t_champs/Douceur-power t_champs/Douceur-power t_champs/Douceur-power > test1
  ./vm_champs/corewar -d $i t_champs/Douceur-power t_champs/Douceur-power t_champs/Douceur-power > test2
  diff test1 test2;
done
