CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

BUILD_DIR = build

TARGETS = main 

all: $(TARGETS)

main: $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ src/graph.cpp src/algorithms.cpp -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGETS)