CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = main.cpp graph.cpp scc.cpp
OUT = program

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# ======================
# Demo (oppgave 3.3)
# ======================

pro22: $(OUT)
	./$(OUT) kb03a.dat

pro25: $(OUT)
	./$(OUT) kb03b.dat

pro31: $(OUT)
	./$(OUT) kb03a.dat

pro32: $(OUT)
	./$(OUT) kb03b.dat qy03b.dat

clean:
	rm -f $(OUT)