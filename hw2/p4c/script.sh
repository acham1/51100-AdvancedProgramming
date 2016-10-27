#!/bin/bash

#./simp
for file in ./test_input/*
do
    ./simp <$file >"$file.output"
done