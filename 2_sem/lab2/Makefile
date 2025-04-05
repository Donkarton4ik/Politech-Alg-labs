build_dir = build
lab1_build_dir = ../lab1/build
lab1_src_dir = ../lab1/src
debug_out = $(build_dir)/debug.out

objects = $(lab1_build_dir)/my_string.o $(build_dir)/basefile.o $(build_dir)/Ifile.o
flags = -g -fsanitize=address -Wall -Wextra -Wpedantic -Wfatal-errors -Werror

#цель по умолчанию
all: $(debug_out)

$(debug_out): $(objects) src/main.cpp
	g++ $(flags) -o $(debug_out) src/main.cpp $(objects)

$(lab1_build_dir)/my_string.o: $(lab1_src_dir)/my_string.cpp $(lab1_src_dir)/my_string.hpp
	g++ $(flags) -c -o $(lab1_build_dir)/my_string.o $(lab1_src_dir)/my_string.cpp

$(build_dir)/basefile.o: src/basefile.cpp src/basefile.hpp
	g++ $(flags) -c -o $(build_dir)/basefile.o src/basefile.cpp

$(build_dir)/Ifile.o: src/Ifile.cpp src/basefile.hpp
	g++ $(flags) -c -o $(build_dir)/Ifile.o src/Ifile.cpp


debug: $(debug_out)
	gdb $(debug_out)

#запуск с ручным вводом
run: $(debug_out)
	./$(debug_out)

