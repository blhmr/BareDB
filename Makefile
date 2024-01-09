CC = gcc
CFLAGS = -Wall -Werror -Iinclude

LIB_SOURCES = $(wildcard src/*.c)
LIB_OBJECTS = $(patsubst src/%.c, build/%.o, $(LIB_SOURCES))

EXAMPLES_SOURCES = $(wildcard examples/*.c)
EXAMPLES_BINARIES = $(EXAMPLES_SOURCES:.c=)

all: $(LIB_OBJECTS) $(EXAMPLES_BINARIES)

$(LIB_OBJECTS): build/%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(EXAMPLES_BINARIES): %: %.c $(LIB_OBJECTS)
	$(CC) $(CFLAGS) $< $(LIB_OBJECTS) -o $@

clean:
	rm -f $(LIB_OBJECTS) $(EXAMPLES_BINARIES)

