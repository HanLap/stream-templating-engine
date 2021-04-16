CC = gcc


### FLAGS ###
CFLAGS = -g \
	-Wall   \
	-Wextra \
	-Werror \
	-Wno-unused-parameter
LDFLAGS =


ifeq ($(RELEASE),)
CFLAGS+= \
	-fsanitize=address \
	-fsanitize=undefined 
LDFLAGS+= \
	-fsanitize=address \
	-fsanitize=undefined	
endif


### DEPENDENCIES ###
DEPS = $(wildcard src/*.h)

SRCS = $(shell find -L src -type f -name "*.c")
OBJS = $(SRCS:src/%.c=build/%.o)


### RECIPES ###
.PHONY: all
all: build/ste

.PHONY: test
test: all
	./test.sh

.PHONY: clean
clean:
	-rm -r build
	

build/%.o: src/%.c $(DEPS) build/.exists
	$(CC) -c -o $@ $< $(CFLAGS)  

build/ste: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

build/.exists:
	mkdir -p build
	touch build/.exists
