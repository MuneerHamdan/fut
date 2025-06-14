#include </usr/include/CSFML/Graphics.h>
#include </usr/include/CSFML/Window.h>
#include <stdio.h>

#define W 500
#define H 500

int main() {

	sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){(sfVector2u){W, H}, (unsigned int)8}, (const char*)"window", (uint32_t)0, (sfWindowState)0, &(const sfContextSettings){24,8,16,4,6,1,1});
	sfRenderWindow_setPosition(window, (sfVector2i){300, 300});

	sfTexture* texture = sfTexture_create((sfVectur2u){30,30};
	sfShader* shader = 

	int eventbool = 0;
	while (sfRenderWindow_isOpen(window)) {

		sfEvent e;
		while ((eventbool = sfRenderWindow_pollEvent(window, &e)) == 1) {

			if (e.type == sfEvtClosed) {
				sfRenderWindow_close(window);
			}
			else if (e.type == sfEvtKeyPressed) {
				if (e.key.code == sfKeyEscape) {
					sfRenderWindow_close(window);
				}
			}
		}

		sfRenderWindow_clear(window, (sfColor){33, 233, 33, 11});

		sfRenderWindow_drawCircleShape(window, circle, (sfRenderStates){ (sfBlendMode){0,0,0,0,0,0}, (sfStencilMode){7,0,{0},{1},{0}}, (sfTransform){{0,1,2,3,4,5,6,7,8}}, (sfCoordinateType)0, texture, shader); 

		sfRenderWindow_display(window);
	}

	sfRenderWindow_destroy(window);

	return 0;
}
