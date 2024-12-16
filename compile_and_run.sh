#!/usr/bin/env bash
# This expects the input file name as the first param and the output name as the second

# Could use this to read flags but ¯\_(ツ)_/¯
FILE_PATH=$1
OUTPUT_NAME=output

g++ $FILE_PATH -o $OUTPUT_NAME
./$OUTPUT_NAME