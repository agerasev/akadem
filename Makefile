CPP  = g++
CC   = gcc
OBJ  = main.o
LIBS = -lSDLmain -lSDL -lSDL_ttf -lGL -lGLU
INCS = 
CXXINCS = 
BIN  = akadem
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $^ -o $@ $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

