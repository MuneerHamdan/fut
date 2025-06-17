#include <CSFML/Graphics.h>
#include <stdlib.h>

#define GRAY (sfColor){33, 33, 33, 255}
#define GREEN (sfColor){33, 211, 177, 255}

#define N 11

int main()
{
	sfRenderWindow*   window = sfRenderWindow_create((const sfVideoMode){{800, 600}, 32}, "SFML window", sfResize | sfClose, sfWindowed, NULL);
	if (!window)
		return EXIT_FAILURE;

	sfCircleShape** circles = (sfCircleShape **)malloc(N * sizeof(sfCircleShape *));

	for (int i = 0; i < N; i++) {
		circles[i] = sfCircleShape_create();
		sfCircleShape_setPosition(circles[i], (sfVector2f){i * 20, i * 20});
		sfCircleShape_setFillColor(circles[i], GREEN);
		sfCircleShape_setRadius(circles[i], 20.0);
	}


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
						sfCircleShape_move(circles[0], (sfVector2f){-10.0, 0.0});
						break;
					case (sfKeyJ):
						sfCircleShape_move(circles[0], (sfVector2f){0.0, 10.0});
						break;
					case (sfKeyK):
						sfCircleShape_move(circles[0], (sfVector2f){0.0, -10.0});
						break;
					case (sfKeyL):
						sfCircleShape_move(circles[0], (sfVector2f){10.0, 0.0});
						break;
					default:
						break;
				}
			}
		}

		sfRenderWindow_clear(window, GRAY);

		for (int i = 0; i < N; i++)
			sfRenderWindow_drawCircleShape(window, circles[i], NULL);

		sfRenderWindow_display(window);
	}

	for (int i = 0; i < N; i++)
		sfCircleShape_destroy(circles[i]);

	sfRenderWindow_destroy(window);
	free(circles);

	return EXIT_SUCCESS;
}
