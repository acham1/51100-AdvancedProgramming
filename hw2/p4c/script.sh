#!/bin/bash

gcc -std=c99 -pedantic -Wall ../p4a/p4a.c ../p4a/p4a_dictionary.c ../p4a/p4a_tree.c -I../p4a -o ./simp
gcc -std=c99 -pedantic -Wall ../p4b/p4b.c ../p4b/p4b_dictionary.c ../p4b/p4b_tree.c -I../p4b -o ./bal

for file in ./test_input/*
do
    bn=$(basename $file)
    ./simp <$file >./test_output/simp.$bn.output
    ./bal <$file >./test_output/bal.$bn.output
done
