echo -n "Enter a number : "
read n
if [ $(($n % 2)) -eq 0 ]
then
echo "Even number"
else
echo "Odd Number"
fi
