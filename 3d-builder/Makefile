CXX  = g++
OBJ  = main.o
LIBS =  -lSDLmain -lSDL -lGL -lGLU
INCS = -Isrc
BIN  = builder
FLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CXX) $^ -o $@ $(LIBS)

main.o: src/main.cpp
	$(CXX) -c $< -o $@ $(FLAGS)
