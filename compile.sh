#!/bin/bash

make VERBOSE=y &> make_output.txt
compiledb --parse make_output.txt
