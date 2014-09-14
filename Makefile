SRC_DIR = ./src
INC_DIR = ./mtrand
OBJ_DIR = ./build
CC = g++
CFLAGS = -O2 -g -Wall -I$(INC_DIR)

SRC = $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h $(INC_DIR)/mtrand.h

all: thinker

thinker: $(OBJ_DIR)/thinker.o $(OBJ_DIR)/test.o $(OBJ_DIR)/mtrand.o $(OBJ_DIR)/print.o $(OBJ_DIR)/init.o $(OBJ_DIR)/feedfwd.o $(OBJ_DIR)/backprop.o $(OBJ_DIR)/training.o
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/thinker.o $(OBJ_DIR)/test.o $(OBJ_DIR)/mtrand.o $(OBJ_DIR)/print.o $(OBJ_DIR)/init.o $(OBJ_DIR)/feedfwd.o $(OBJ_DIR)/backprop.o $(OBJ_DIR)/training.o

$(OBJ_DIR)/mtrand.o: $(INC_DIR)/mtrand.cpp $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c $(INC_DIR)/mtrand.cpp

$(OBJ_DIR)/print.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/print.cpp

$(OBJ_DIR)/init.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/init.cpp

$(OBJ_DIR)/feedfwd.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/feedfwd.cpp

$(OBJ_DIR)/backprop.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/backprop.cpp

$(OBJ_DIR)/training.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/training.cpp

$(OBJ_DIR)/test.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/test.cpp

$(OBJ_DIR)/thinker.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/thinker.cpp

clean:
	$(RM) thinker $(OBJ_DIR)/*.o *~
