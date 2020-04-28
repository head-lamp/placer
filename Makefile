objs = main.cpp
cc = g++
compiler_flags = -w -v
# linker_flags = -I include -L lib -l SDL2-2.0.0 -lSDL2_image
linker_flags = -I /usr/local/include -L /usr/local/lib -l SDL2-2.0.0 -lSDL2_image
obj_name = game

all : $(objs)
	$(cc) $(objs) $(compiler_flags) $(linker_flags) -o $(obj_name)
	./game
