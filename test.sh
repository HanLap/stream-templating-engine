#!/bin/bash

  red="$(tput setaf 1)" ; export red
green="$(tput setaf 2)" ; export green
reset="$(tput sgr0)"    ; export reset

failed=""

cd test
for input in *.input; do
  name=$(basename -s .input $input)
  expected="${name}.expected"
  variables=$(cat "${name}.variables")

  # run ste and timeout if it takes to long
  actual=$(timeout 1 ../build/ste -p "<#{" -P "}#>" -v "$variables" "$input")
  # actual="a b c d e f g h i"
  timeout="$?"

  diff=$(echo $actual | diff -q "./$expected" -)

  if   [ "$timeout" == "124" ]; then
    failed="YES"
    printf "%-20s %20s\n" $name "[${red}TIMEOUT${reset}]"

  elif [ "$diff"             ]; then
    failed="YES"
    printf "%-20s %20s\n" $name "[${red}FAILED${reset}]"
    echo "$(echo $actual | 
            diff --color="always" \
                 "./$expected" -)"

  else 
    printf "%-20s %20s\n" $name "[${green}OK${reset}]"
  fi

done

# if [ $failed ]; then
#   exit 1
# else 
#   exit 0
# fi