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
DEPS = $(wildcard *.h)

SRCS = $(shell find -L . -type f -name "*.c")
OBJS = $(addprefix build/,$(SRCS:.c=.o))


### RECIPES ###
.PHONY: all
all: build/ste

build/%.o: %.c $(DEPS) build/.exists
	$(CC) -c -o $@ $< $(CFLAGS)  

build/ste: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


build/.exists:
	mkdir -p build
	touch build/.exists


.PHONY: clean
clean:
	-rm -r build