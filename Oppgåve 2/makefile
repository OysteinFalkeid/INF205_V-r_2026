CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

BUILD_DIR = build

TARGETS = problem-2-1 problem-2-2 problem-2-3 problem-2-4 problem-2-5 problem-2-6

all: $(TARGETS)

problem-2-1: $(BUILD_DIR)/problem-2-1.o
	$(CXX) $(CXXFLAGS) $^ -o $@

problem-2-2: $(BUILD_DIR)/problem-2-2.o
	$(CXX) $(CXXFLAGS) $^ -o $@

problem-2-3: $(BUILD_DIR)/problem-2-3.o
	$(CXX) $(CXXFLAGS) $^ -o $@

problem-2-4: $(BUILD_DIR)/problem-2-4.o
	$(CXX) $(CXXFLAGS) $^ -o $@

problem-2-5: $(BUILD_DIR)/problem-2-5.o
	$(CXX) $(CXXFLAGS) $^ -o $@

problem-2-6: $(BUILD_DIR)/problem-2-6.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGETS)