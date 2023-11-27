#!/bin/bash

for i in `seq -f %02g 2 25`
do
  cat "AOC 01/hard/hard.cpp" | sed -e "s|AOC 01|AOC ${i}|g" > "AOC ${i}/hard/hard.cpp"
  cat "AOC 01/simple/simple.cpp" | sed -e "s|AOC 01|AOC ${i}|g" > "AOC ${i}/simple/simple.cpp"
  cat "AOC 01/test/test.cpp" | sed -e "s|AOC 01|AOC ${i}|g" > "AOC ${i}/test/test.cpp"
  
  echo "test ${i}" > "AOC ${i}/data/test.txt"
  echo "simple ${i}" > "AOC ${i}/data/simple.txt"
  echo "hard ${i}" > "AOC ${i}/data/hard.txt"
  
  cat "AOC 01/hard/hard.vcxproj" | sed -e "s|-0001-|-00${i}-|g" -e "s|AOC 01|AOC ${i}|g" > "AOC ${i}/hard/hard.vcxproj"
  cat "AOC 01/simple/simple.vcxproj" | sed -e "s|-0001-|-00${i}-|g" -e "s|AOC 01|AOC ${i}|g" > "AOC ${i}/simple/simple.vcxproj"
  cat "AOC 01/test/test.vcxproj" | sed -e "s|-0001-|-00${i}-|g" -e "s|AOC 01|AOC ${i}|g" > "AOC ${i}/test/test.vcxproj"
   
done  
