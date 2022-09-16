echo "Enter Year"
read y
if [ $(($y % 4)) -eq 0 ]
then
echo "It's a leap year"
else
echo "It's not a leap year"
fi
