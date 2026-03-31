CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = main.cpp graph.cpp scc.cpp measure.cpp
OUT = program

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)


# Demo (oppgave 3.3)


pro22: $(OUT)
	./$(OUT) pro22

pro25: $(OUT)
	./$(OUT) pro25

pro31: $(OUT)
	./$(OUT) pro31

pro32: $(OUT)
	./$(OUT) pro32

clean:
	rm -f $(OUT)
