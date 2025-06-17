#include </usr/include/CSFML/Graphics.h>
#include </usr/include/CSFML/Window.h>
#include <stdio.h>
 
#define W 600
#define H 400
#define GRAY (sfColor){18,18,18,18}
#define GREEN (sfColor){33, 233, 33, 11}
int main() {

	sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){(sfVector2u){W, H}, (unsigned int)8}, (const char*)"window", (uint32_t)0, (sfWindowState)0, &(const sfContextSettings){24,8,16,4,6,1,1});
	sfRenderWindow_setPosition(window, (sfVector2i){300, 300});


	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setPosition(circle, (sfVector2f){250.0, 250.0});
	sfCircleShape_setFillColor(circle, GREEN);
	sfCircleShape_setRadius(circle, 300.0);


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

		sfRenderWindow_clear(window, GRAY);

		sfRenderWindow_drawCircleShape(window, circle, NULL);
//		printf("%d ", sfRenderWindow_getSize(window).x);
//		printf("%d ", sfRenderWindow_getPosition(window).x);
		//printf("%f ", sfCircleShape_getRadius(circle));

		sfRenderWindow_display(window);
	}

	sfCircleShape_destroy(circle);
	sfRenderWindow_destroy(window);

	return 0;
}
