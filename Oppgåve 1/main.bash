#!/bin/bash
echo "Building executables"
make
export PATH=".:$PATH"
echo "-----------------------------------------------------------------"
echo "problem-1-1"
echo ""
problem-1-1
echo "-----------------------------------------------------------------"
echo "problem-1-2"
echo ""
problem-1-2
echo "-----------------------------------------------------------------"
echo "problem-1-3"
echo ""
problem-1-3
echo "-----------------------------------------------------------------"
echo "problem-1-4"
echo ""
problem-1-4
echo "-----------------------------------------------------------------"
echo "problem-1-5"
echo ""
echo "problem-1-5 -l -l -f -r -d -e 20 -e -l"
problem-1-5 -l -l -f -r -d -e 20 -e -l
echo "-----------------------------------------------------------------"
echo "problem-1-6"
echo ""
problem-1-6