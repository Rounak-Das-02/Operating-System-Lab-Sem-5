read -p "First file name : " file1
read -p "Second file name : " file2
if diff -u "$file1" "$file2"; then
  echo "$file1 and $file2 have identical contents"
else
:
   # the differences between the files have been listed
fi
