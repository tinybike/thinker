CC=g++
CFLAGS=-O2 -g -Wall -Wextra -rdynamic -Isrc $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.cpp src/**/*.h src/*.cpp src/*.h)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

BUILD=build/libthinker.a
TARGET=bin/thinker

all: $(BUILD) $(TARGET)

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(BUILD): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

clean:
	$(RM) thinker build/*.a build/*.o src/*.o src/**/*.o *~

BADS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@egrep $(BADS) $(SOURCES) || true
