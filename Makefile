cc = g++
compiler_flags = -w -v
# linker_flags = -I include -L lib -l SDL2-2.0.0 -lSDL2_image -lSDL2_ttf
linker_flags = -I /usr/local/include -L /usr/local/lib -l SDL2-2.0.0 -lSDL2_image

out=game

obj_files =\
	main.o \
	game.o \
	config.o \

$(out) : $(obj_files)
	$(cc) $(compiler_flags) -o $(out) $(obj_files) $(linker_flags)

.c.o: ; $(cc) -c $(compiler_flags) -o $@ $*.c
