#!/bin/bash

make VERBOSE=y run &> make_output.txt
compiledb --parse make_output.txt
