build_dir = build
lab1_build_dir = build/lab1_build
lab1_src_dir = src/lab1_src
debug_out = $(build_dir)/debug.out

objects = $(lab1_build_dir)/my_string.o $(lab1_build_dir)/matrix.o
flags = -g -fsanitize=address -Wall -Wextra -Wpedantic -Wfatal-errors -Werror

#цель по умолчанию
all: $(debug_out)

$(debug_out): $(objects) src/main.cpp
	g++ $(flags) -o $(debug_out) src/main.cpp $(objects)

$(lab1_build_dir)/my_string.o: $(lab1_src_dir)/my_string.cpp $(lab1_src_dir)/my_string.hpp
	g++ $(flags) -c -o $(lab1_build_dir)/my_string.o $(lab1_src_dir)/my_string.cpp

$(lab1_build_dir)/matrix.o: $(lab1_src_dir)/matrix.cpp $(lab1_src_dir)/matrix.hpp
	g++ $(flags) -c -o $(lab1_build_dir)/matrix.o $(lab1_src_dir)/matrix.cpp



debug: $(debug_out)
	gdb $(debug_out)

#запуск с ручным вводом
run: $(debug_out)
	./$(debug_out)

