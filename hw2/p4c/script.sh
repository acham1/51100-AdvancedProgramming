#!/bin/bash

gcc -std=c99 -pedantic -Wall ../p4a.c ../p4a_dictionaryc ../p4a_tree.c -I../
gcc -std=c99 -pedantic -Wall ../p4b.c ../p4b_dictionaryc ../p4v_tree.c -I../

for file in ./test_input/*
do
    ./simp <$file >"$file.output"
done