build_dir = build
debug_out = $(build_dir)/debug.out

objects = $(build_dir)/rect.o $(build_dir)/my_string.o $(build_dir)/barrel.o $(build_dir)/text_wrapper.o $(build_dir)/matrix.o
flags = -g -fsanitize=address -Wall -Wextra -Wpedantic -Wfatal-errors -Werror

#цель по умолчанию
all: $(debug_out)

$(build_dir)/rect.o: src/rect.cpp src/rect.hpp | $(build_dir)
	g++ $(flags) -c -o $(build_dir)/rect.o src/rect.cpp

$(build_dir)/my_string.o: src/my_string.cpp src/my_string.hpp | $(build_dir)
	g++ $(flags) -c -o $(build_dir)/my_string.o src/my_string.cpp

$(build_dir)/barrel.o: src/barrel.cpp src/barrel.hpp | $(build_dir)
	g++ $(flags) -c -o $(build_dir)/barrel.o src/barrel.cpp

$(build_dir)/text_wrapper.o: src/text_wrapper.cpp src/text_wrapper.hpp | $(build_dir)
	g++ $(flags) -c -o $(build_dir)/text_wrapper.o src/text_wrapper.cpp

$(build_dir)/matrix.o: src/matrix.cpp src/matrix.hpp | $(build_dir)
	g++ $(flags) -c -o $(build_dir)/matrix.o src/matrix.cpp

$(debug_out): $(objects) src/main.cpp | $(build_dir)
	g++ $(flags) -o $(debug_out) src/main.cpp $(objects)

#создание папки build, если ее нет
$(build_dir):
	mkdir -p $(build_dir)

debug: $(debug_out)
	gdb $(debug_out)

#верисия для проверки утечек; debug_out потому чир в нем и так есть -fsanitize
leaks: $(debug_out)
	./$(debug_out) < input.txt

#запуск с ручным вводом
run: $(debug_out)
	./$(debug_out)

#удаление папки build
clean:
	rm -rf $(build_dir)


$(build_dir)/test_rect_basic_methods.out: tests/test_rect_basic_methods.cpp src/rect.cpp src/rect.hpp | $(build_dir)
	g++ $(flags) -o $(build_dir)/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp src/rect.cpp

$(build_dir)/test_rect_properties.out: tests/test_rect_properties.cpp src/rect.cpp src/rect.hpp | $(build_dir)
	g++ $(flags) -o $(build_dir)/test_rect_properties.out tests/test_rect_properties.cpp src/rect.cpp

$(build_dir)/test_rect_operations.out: tests/test_rect_operations.cpp src/rect.cpp src/rect.hpp | $(build_dir)
	g++ $(flags) -o $(build_dir)/test_rect_operations.out tests/test_rect_operations.cpp src/rect.cpp

$(build_dir)/test_bounding_rect.out: tests/test_bounding_rect.cpp src/rect.cpp src/rect.hpp | $(build_dir)
	g++ $(flags) -o $(build_dir)/test_bounding_rect.out tests/test_bounding_rect.cpp src/rect.cpp

run_test_rect_basic_methods: $(build_dir)/test_rect_basic_methods.out
	./$(build_dir)/test_rect_basic_methods.out

run_test_rect_properties: $(build_dir)/test_rect_properties.out
	./$(build_dir)/test_rect_properties.out

run_test_rect_operations: $(build_dir)/test_rect_operations.out
	./$(build_dir)/test_rect_operations.out

run_test_bounding_rect: $(build_dir)/test_bounding_rect.out
	./$(build_dir)/test_bounding_rect.out

test: run_test_rect_basic_methods run_test_rect_properties run_test_rect_operations run_test_bounding_rect