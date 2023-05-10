#!/usr/bin/env bash
executableFileName="${1:-cpsc351Program}"

temp=$IFS
  IFS=$'\n'  
  sourceFiles=( $(find ./ -name "*.c") )
IFS=$temp

echo "compiling ..."
for fileName in "${sourceFiles[@]}"; do
  echo "  $fileName"
done
echo ""

options="-g3 -O0 -pthread  -I./ -DUSING_TOMS_SUGGESTIONS"
gcc $options -o "$executableFileName" "${sourceFiles[@]}" -lrt && echo -e "\nSuccessfully created  \"$executableFileName\""
