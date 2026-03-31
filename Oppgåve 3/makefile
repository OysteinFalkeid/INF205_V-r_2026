CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

BUILD_DIR = build

TARGETS = main problem34 bencgraph_benchmarkmark graph_benchmark_scc problem22_target problem25_target problem31_target problem32_target

all: $(TARGETS)

main: $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

problem34: $(BUILD_DIR)/problem34.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

graph_benchmark: $(BUILD_DIR)/graph-benchmark.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

graph_benchmark_scc: $(BUILD_DIR)/graph-benchmark-scc.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGETS)

# ======================
# Demo (oppgave 3.3)
# ======================

problem22_target: $(BUILD_DIR)/problem22.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

problem25_target: $(BUILD_DIR)/problem25.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

problem31_target: $(BUILD_DIR)/problem31.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

problem32_target: $(BUILD_DIR)/problem32.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


problem22: problem22_target
	./problem22_target -f graph_inn.txt

problem25: problem25_target
	./problem25_target -f graph_inn.txt

problem31: problem31_target
	./problem31_target -f scc-graph-benchmark-data/scc06.dat

problem32: problem32_target
	./problem32_target -f knowledge-graph-benchmark-data/kb04a.dat --rpq knowledge-graph-benchmark-data/qy04a.dat