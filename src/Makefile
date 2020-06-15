cc = g++
compiler_flags = -w -v -Wall -std='c++14'
# linker_flags = -I include -L lib -l SDL2-2.0.0 -lSDL2_image -lSDL2_
linker_flags = -I /usr/local/include -L /usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf

out=game

obj_files =\
	main.o \
	game.o \
	config.o \
	log.o \
	graphics.o \
	physical.o \
	renderable.o \
	game_world.o \
	startmenu.o \
	editor.o \
	map.o \
	util.o \
	lib/cJSON.o

$(out) : $(obj_files)
	$(cc) $(compiler_flags) -o $(out) $(obj_files) $(linker_flags)

.c.o: ; $(cc) -c $(compiler_flags) -o $@ $*.c
