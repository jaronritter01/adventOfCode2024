#!/usr/bin/env bash

# Could use this to read flags but ¯\_(ツ)_/¯
FILE_PATH=$1
OUTPUT_NAME=$2

g++ $FILE_PATH -o $OUTPUT_NAME
./$OUTPUT_NAME