CC := gcc

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm 

HDRS := sources/struct.h sources/common.h sources/init.h sources/defs.h sources/input.h sources/draw.h sources/loadMedia.h

SRCS := sources/main.c sources/init.c sources/input.c sources/draw.c sources/loadMedia.c

OBJS := $(SRCS:.c=.o)

EXEC := level

all: $(EXEC)

showfont: showfont.c makefile
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

glfont: glfont.c makefile
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

$(EXEC): $(OBJS) $(HDRS) makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) makefile
#    $(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean