#include </usr/include/CSFML/Graphics.h>
#include </usr/include/CSFML/Window.h>
#include <stdio.h>

#define W 500
#define H 500

int main() {

	sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){(sfVector2u){W, H}, (unsigned int)8}, (const char*)"window", (uint32_t)0, (sfWindowState)0, &(const sfContextSettings){24,8,16,4,6,1,1});

	sfRenderWindow_setPosition(window, (sfVector2i){300, 300});

	sfColor color = {110,10,10,10};

	int eventbool = 0;
	while (sfRenderWindow_isOpen(window)) {
		sfEvent e;
		printf("%d\n", e.type);

		while ((eventbool = sfRenderWindow_pollEvent(window, &e)) == 1) {
			if (e.type == sfEvtClosed) {
				sfRenderWindow_close(window);
			}
			if (e.key.code == sfKeyEscape) {
				sfRenderWindow_close(window);
			}
		}
		sfRenderWindow_clear(window, color);
		sfRenderWindow_display(window);
	}

	sfRenderWindow_destroy(window);

	return 0;
}
