SRC_DIR = ./src
INC_DIR = ./mtrand
OBJ_DIR = ./build
CC = g++
CFLAGS = -O2 -g -Wall -I$(INC_DIR)

all: thinker

thinker: $(OBJ_DIR)/thinker.o $(OBJ_DIR)/test.o $(OBJ_DIR)/mtrand.o
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/thinker.o $(OBJ_DIR)/test.o $(OBJ_DIR)/mtrand.o

$(OBJ_DIR)/test.o: $(SRC_DIR)/test.cpp $(SRC_DIR)/test.h $(SRC_DIR)/thinker.h $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/test.cpp

$(OBJ_DIR)/thinker.o: $(SRC_DIR)/thinker.cpp $(SRC_DIR)/thinker.h $(SRC_DIR)/test.h $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/thinker.cpp

$(OBJ_DIR)/mtrand.o: $(INC_DIR)/mtrand.cpp $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c $(INC_DIR)/mtrand.cpp

clean:
	$(RM) thinker $(OBJ_DIR)/*.o *~
