#include <CSFML/Graphics.h>
#include <stdlib.h>

#define GRAY (sfColor){18, 18, 18, 255}
#define GREEN (sfColor){33, 211, 177, 255}

int main(void)
{
	sfRenderWindow*   window = sfRenderWindow_create((const sfVideoMode){{800, 600}, 32}, "SFML window", sfResize | sfClose, sfWindowed, NULL);
	if (!window)
		return EXIT_FAILURE;


	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setPosition(circle, (sfVector2f){200, 200});
	sfCircleShape_setFillColor(circle, GREEN);
	sfCircleShape_setRadius(circle, 20.0);


	sfEvent event;
	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
			if (event.type == sfEvtKeyPressed) {
				switch (event.key.code) {
					case (sfKeyEscape):
						sfRenderWindow_close(window);
						break;
					case (sfKeyLControl && sfKeyC):
						sfRenderWindow_close(window);
						break;
					case (sfKeyH):
						sfCircleShape_move(circle, (sfVector2f){-10.0, 0.0});
						break;
					case (sfKeyJ):
						sfCircleShape_move(circle, (sfVector2f){0.0, 10.0});
						break;
					case (sfKeyK):
						sfCircleShape_move(circle, (sfVector2f){0.0, -10.0});
						break;
					case (sfKeyL):
						sfCircleShape_move(circle, (sfVector2f){10.0, 0.0});
						break;
					default:
						break;
				}
			}
		}

		sfRenderWindow_clear(window, GRAY);

		sfRenderWindow_drawCircleShape(window, circle, NULL);

		sfRenderWindow_display(window);
	}

	sfCircleShape_destroy(circle);
	sfRenderWindow_destroy(window);

	return EXIT_SUCCESS;
}
