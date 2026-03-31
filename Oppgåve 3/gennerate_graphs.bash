
# for ((nodes = 100; nodes<1000; nodes+=100)); do
#     echo $nodes
#     for ((edges = 100; edges < 1000; edges += 100)); do
#         echo $edges
#         ./graph_benchmark_scc $nodes $edges graph_scc.dat >> output_1.txt
#         ./problem34 -v -f graph_scc.dat -r 10 --tarjans >> output_1.txt
#     done
# done

for ((nodes = 100; nodes<1000; nodes+= 100)); do
    echo $nodes
    for ((edges = 1; edges < 10; edges += 1)); do
        echo $edges
        echo $nodes " " $edges >> output_1.txt
        ./graph_benchmark $nodes $edges graph_scc.dat qtgraph_scc.dat
        ./problem34 -v -f graph_scc.dat -r 10 --rpq qtgraph_scc.dat >> output_1.txt
    done
done


# ./graph_benchmark 10 10 graph_scc.dat qtgraph_scc.dat
# ./problem34 -v -f graph_scc.dat -r 10 --rpq qtgraph_scc.dat
