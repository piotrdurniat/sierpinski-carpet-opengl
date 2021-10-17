
CXX       := g++
CXX_FLAGS := -lGL -lglut

BIN     := bin
SRC     := src

LIBRARIES   :=
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $^ $(CXX_FLAGS) -o $@ $(LIBRARIES)


clean:
	rm $(BIN)/*