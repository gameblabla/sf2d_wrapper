CC = gcc

CFLAGS = -O0 -g -I. `sdl2-config --cflags` -DUNIX -I../../Wrapper/SDL2 -I/usr/include/SDL2
LDFLAGS = `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_gfx -lSDL2_ttf
OUTPUT = memory3ds

SOURCES = main.c \
../../Wrapper/SDL2/sf2d.c ../../Wrapper/SDL2/3ds.c
OBJS = ${SOURCES:.c=.o}

${OUTPUT}:${OBJS}
	${CC} -o ${OUTPUT} ${OBJS} ${CFLAGS} ${LDFLAGS} ${DEFINES} 
	
clean:
	rm *.o
	rm ${OUTPUT}
