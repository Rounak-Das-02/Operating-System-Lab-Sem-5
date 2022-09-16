for program in *.c ;
do
    gcc -o my_program $program
./my_program
rm my_program
done
