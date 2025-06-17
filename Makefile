file=fut
all: $(file)

$(file):
	gcc $(file).c -o $(file).out -Wall -Werror -fsanitize=undefined,address -g -lcsfml-graphics -lcsfml-window -lcsfml-system
	./$(file).out

clean:
	rm $(file).out
