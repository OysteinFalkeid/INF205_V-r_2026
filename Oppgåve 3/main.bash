make clean
make
echo
echo "3a ------------------"
./main -f knowledge-graph-benchmark-data/kb03a.dat --rpq knowledge-graph-benchmark-data/qy03a.dat
echo
echo "3b ------------------"
./main -f knowledge-graph-benchmark-data/kb03b.dat --rpq knowledge-graph-benchmark-data/qy03b.dat
echo
echo "4a ------------------"
./main -f knowledge-graph-benchmark-data/kb04a.dat --rpq knowledge-graph-benchmark-data/qy04a.dat
echo
echo "4b ------------------"
./main -f knowledge-graph-benchmark-data/kb04b.dat --rpq knowledge-graph-benchmark-data/qy04b.dat
echo
echo "6a ------------------"
./main -f knowledge-graph-benchmark-data/kb06a.dat --rpq knowledge-graph-benchmark-data/qy06a.dat
echo
echo "6b ------------------"
./main -f knowledge-graph-benchmark-data/kb06b.dat --rpq knowledge-graph-benchmark-data/qy06b.dat
echo
echo "9a ------------------"
./main -f knowledge-graph-benchmark-data/kb09a.dat --rpq knowledge-graph-benchmark-data/qy09a.dat
echo
echo "9b ------------------"
./main -f knowledge-graph-benchmark-data/kb09b.dat --rpq knowledge-graph-benchmark-data/qy09b.dat
echo
echo "13a ------------------"
./main -f knowledge-graph-benchmark-data/kb13a.dat --rpq knowledge-graph-benchmark-data/qy13a.dat
echo
echo "13b ------------------"
./main -f knowledge-graph-benchmark-data/kb13b.dat --rpq knowledge-graph-benchmark-data/qy13b.dat
echo