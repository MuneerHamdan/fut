file=sfml
all: $(file)

sfml:
	gcc $(file).c -o $(file).out -Wall -Werror -fsanitize=undefined,address -g -lcsfml-graphics -lcsfml-window
	./$(file).out

clean:
	rm *.out
