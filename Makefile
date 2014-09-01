INC_DIR = ./mtrand
OBJ_DIR = ./build
CC = g++
CFLAGS = -O2 -g -Wall -Werror -I$(INC_DIR)

all: thinker

thinker: $(OBJ_DIR)/thinker.o $(OBJ_DIR)/mtrand.o
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/thinker.o $(OBJ_DIR)/mtrand.o

$(OBJ_DIR)/thinker.o: thinker.cpp thinker.h $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c thinker.cpp

$(OBJ_DIR)/mtrand.o: $(INC_DIR)/mtrand.cpp $(INC_DIR)/mtrand.h
	$(CC) $(CFLAGS) -o $@ -c $(INC_DIR)/mtrand.cpp

clean:
	$(RM) thinker $(OBJ_DIR)/*.o *~
