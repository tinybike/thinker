INC_DIR = ./mtrand
OBJ_DIR = ./build
CC = g++
CFLAGS = -O2 -g -Wall -Werror -I$(INC_DIR)

all: neuralnet

neuralnet: $(OBJ_DIR)/neuralnet.o $(OBJ_DIR)/mtrand.o
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/neuralnet.o $(OBJ_DIR)/mtrand.o

$(OBJ_DIR)/neuralnet.o: neuralnet.cpp neuralnet.h $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c neuralnet.cpp

$(OBJ_DIR)/mtrand.o: $(INC_DIR)/mtrand.cpp $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c $(INC_DIR)/mtrand.cpp

clean:
	$(RM) neuralnet $(OBJ_DIR)/*.o *~
