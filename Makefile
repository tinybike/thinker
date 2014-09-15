SRC_DIR = src
INC_DIR = src/mtrand
OBJ_DIR = build
CC = g++
CFLAGS = -O2 -g -Wall -I$(INC_DIR)

SRC = $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h $(INC_DIR)/mtrand.h

all: bin/thinker
	@mkdir -p build
	@mkdir -p bin

bin/thinker: $(OBJ_DIR)/thinker.o $(OBJ_DIR)/test.o $(OBJ_DIR)/mtrand.o $(OBJ_DIR)/print.o $(OBJ_DIR)/innervate.o $(OBJ_DIR)/forward.o $(OBJ_DIR)/backward.o $(OBJ_DIR)/train.o
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/thinker.o $(OBJ_DIR)/test.o $(OBJ_DIR)/mtrand.o $(OBJ_DIR)/print.o $(OBJ_DIR)/innervate.o $(OBJ_DIR)/forward.o $(OBJ_DIR)/backward.o $(OBJ_DIR)/train.o

$(OBJ_DIR)/mtrand.o: $(INC_DIR)/mtrand.cpp $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c $(INC_DIR)/mtrand.cpp

$(OBJ_DIR)/print.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/print.cpp

$(OBJ_DIR)/innervate.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/innervate.cpp

$(OBJ_DIR)/forward.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/forward.cpp

$(OBJ_DIR)/backward.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/backward.cpp

$(OBJ_DIR)/train.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/train.cpp

$(OBJ_DIR)/test.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/test.cpp

$(OBJ_DIR)/thinker.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $(SRC_DIR)/thinker.cpp

clean:
	$(RM) bin/thinker $(OBJ_DIR)/*.o *~
