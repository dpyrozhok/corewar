i=1600
while [ $i -le 20000 ]
do
   echo $i;
  i=$(( i + 1));
  ./corewar -dump $i t_champs/Kittystrophic.cor t_champs/Kittystrophic.cor t_champs/Kittystrophic.cor t_champs/Kittystrophic.cor > test1
  ./vm_champs/corewar -d $i t_champs/Kittystrophic.cor t_champs/Kittystrophic.cor t_champs/Kittystrophic.cor t_champs/Kittystrophic.cor > test2
  diff test1 test2;
done
