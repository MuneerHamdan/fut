#include <CSFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>

#define GRAY (sfColor){77, 77, 77, 255}
#define GREEN (sfColor){55, 255, 155, 255}

#define N 11


void initcircles(const unsigned int W, const unsigned int H, sfCircleShape** circles) {
	float RADIUS = (W / N) / N;
	for (int i = 0; i < N; i++) {
		circles[i] = sfCircleShape_create();
		sfCircleShape_setPosition(circles[i], (sfVector2f){(i * (W / N)), (i * (H / N))});
		sfCircleShape_setFillColor(circles[i], GREEN);
		sfCircleShape_setRadius(circles[i], RADIUS);
	}
}

int main()
{
	sfVideoMode desk = sfVideoMode_getDesktopMode();
	const unsigned int deskx = desk.size.x;
	const unsigned int desky = desk.size.y;


	const unsigned int W = deskx / 2;
	const unsigned int H = desky / 2;

	sfRenderWindow* window = sfRenderWindow_create(
			(const sfVideoMode){{W, H}, 32},
			"SFML window",
			sfNone,
			sfWindowed,
			NULL
			);
	if (!window)
		return EXIT_FAILURE;
	sfRenderWindow_setPosition(window, (sfVector2i){(deskx / 2) - (W / 2), (desky / 2) - (H / 2)});

	sfCircleShape** circles = (sfCircleShape **)malloc(N * sizeof(sfCircleShape *));

	initcircles(W, H, circles);


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


	//done
	for (int i = 0; i < N; i++)
		sfCircleShape_destroy(circles[i]);

	sfRenderWindow_destroy(window);
	free(circles);

	return EXIT_SUCCESS;
}
