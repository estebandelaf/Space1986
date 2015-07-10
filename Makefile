APP=Space1986
OBJS=SDL.o Nave.o Enemigo.o
CPPFLAGS=-ggdb -Wall
all: $(OBJS)
	g++ $(CPPFLAGS) $(APP).cpp $(OBJS) -o $(APP) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
clean:
	rm -f $(APP) *.o
