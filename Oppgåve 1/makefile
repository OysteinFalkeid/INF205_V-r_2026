CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

BUILD_DIR = build

TARGETS = problem-1-1 problem-1-2 problem-1-3 problem-1-4 problem-1-5 problem-1-6

all: $(TARGETS)

problem-1-1: $(BUILD_DIR)/problem-1-1.o
	$(CXX) $(CXXFLAGS) $^ -o $@

problem-1-2: $(BUILD_DIR)/problem-1-2.o
	$(CXX) $(CXXFLAGS) $^ -o $@

problem-1-3: $(BUILD_DIR)/problem-1-3.o
	$(CXX) $(CXXFLAGS) $^ src/journal-article-index.cpp -o $@

problem-1-4: $(BUILD_DIR)/problem-1-4.o
	$(CXX) $(CXXFLAGS) $^ src/book-index.cpp -o $@

problem-1-5: $(BUILD_DIR)/problem-1-5.o
	$(CXX) $(CXXFLAGS) $^ -o $@

problem-1-6: $(BUILD_DIR)/problem-1-6.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGETS)
