EXE=Fishing_Game

all:$(EXE)

Fishing_Game:Fishing_Game.o
	cc -o Fishing_Game Fishing_Game.o

Fishing_Game.o:Fishing_Game.c
	cc -c Fishing_Game.c

clean:
	rm -rf Fishing_Game Fishing_Game.o