#include <CSFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GRAY (sfColor){77, 77, 77, 255}
#define GREEN (sfColor){55, 255, 155, 255}

#define N 1
#define RADIUS 30.0


void initcircles(const unsigned int W, const unsigned int H, sfCircleShape** circles) {
	//float RADIUS = 100.0;
	for (int i = 0; i < N; i++) {
		circles[i] = sfCircleShape_create();
		sfCircleShape_setRadius(circles[i], RADIUS);
		sfCircleShape_setOrigin(circles[i], (sfVector2f){sfCircleShape_getRadius(circles[i]), sfCircleShape_getRadius(circles[i])});
		sfCircleShape_setPosition(circles[i], (sfVector2f){(i * (W / N)), (i * (H / N))});
		sfCircleShape_setFillColor(circles[i], GREEN);
	}
}

void init433(const unsigned int W, const unsigned int H, sfCircleShape** circles) {

	sfCircleShape_setPosition(circles[0], (sfVector2f){(W - (RADIUS * 2.0)) / 2.0, H - (2.0 * RADIUS)});
	sfCircleShape_setPosition(circles[1], (sfVector2f){(W - (RADIUS * 2.0)), ((H * 3.0 / 4.0) - (2.0 * RADIUS))});
	sfCircleShape_setPosition(circles[2], (sfVector2f){(W - (RADIUS * 2.0)) / 3.0, ((H * 3.0 / 4.0) - (2.0 * RADIUS))});
	sfCircleShape_setPosition(circles[3], (sfVector2f){(0.0), ((H * 3.0 / 4.0) - (2.0 * RADIUS))});
	sfCircleShape_setPosition(circles[4], (sfVector2f){(W - (RADIUS * 2.0)) / 2.0, H - (2.0 * RADIUS)});
	sfCircleShape_setPosition(circles[5], (sfVector2f){(W - (RADIUS * 2.0)) / 2.0, H - (2.0 * RADIUS)});
	sfCircleShape_setPosition(circles[6], (sfVector2f){(W - (RADIUS * 2.0)) / 2.0, H - (2.0 * RADIUS)});
	sfCircleShape_setPosition(circles[7], (sfVector2f){(W - (RADIUS * 2.0)) / 2.0, H - (2.0 * RADIUS)});
	sfCircleShape_setPosition(circles[8], (sfVector2f){(W - (RADIUS * 2.0)) / 2.0, H - (2.0 * RADIUS)});
	sfCircleShape_setPosition(circles[9], (sfVector2f){(W - (RADIUS * 2.0)) / 2.0, H - (2.0 * RADIUS)});
	sfCircleShape_setPosition(circles[10], (sfVector2f){(W - (RADIUS * 2.0)) / 2.0, H - (2.0 * RADIUS)});
}

typedef struct circle {
	char num;
	sfCircleShape* circle;
	sfVector2f pos;
	float radius;
	sfColor color;
} Circle;

void initcircle(Circle* c, char num, sfVector2f pos, float radius, sfColor color) {
	c->num = num;
	c->circle = sfCircleShape_create();
	c->pos = pos;
	c->radius = radius;
	c->color = color;
	sfCircleShape_setRadius(c->circle, radius);
	sfCircleShape_setOrigin(c->circle, (sfVector2f){radius, radius});
	sfCircleShape_setPosition(c->circle, pos);
	sfCircleShape_setFillColor(c->circle, color);
}

void movetowards(Circle* a, Circle* b) {
	float x = a->pos.x - b->pos.x;
	float y = a->pos.y - b->pos.y;
	printf("(%f, %f)\n", fabs(x), fabs(y));
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
		return -1;
	sfRenderWindow_setPosition(window, (sfVector2i){(deskx / 2) - (W / 2), (desky / 2) - (H / 2)});

//	sfCircleShape** circles = (sfCircleShape **)malloc(N * sizeof(sfCircleShape *));

//	initcircles(W, H, circles);

//	init433(W, H, circles);

	Circle ball;
	initcircle(&ball, '0', (sfVector2f){W / 2.0, H / 2.0}, 15.0, (sfColor){255,12,123, 255});

	Circle player1;
	initcircle(&player1, '1', (sfVector2f){W / 3.0, H / 2.0}, 30.0, GREEN);
	

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
//						sfCircleShape_move(circles[0], (sfVector2f){-10.0, 0.0});
						break;
					case (sfKeyJ):
//						sfCircleShape_move(circles[0], (sfVector2f){0.0, 10.0});
						break;
					case (sfKeyK):
//						sfCircleShape_move(circles[0], (sfVector2f){0.0, -10.0});
						break;
					case (sfKeyL):
//						sfCircleShape_move(circles[0], (sfVector2f){10.0, 0.0});
						break;
					default:
						break;
				}
			}
		}

		sfRenderWindow_clear(window, GRAY);

//		for (int i = 0; i < N; i++)
//			sfRenderWindow_drawCircleShape(window, circles[i], NULL);

		sfRenderWindow_drawCircleShape(window, ball.circle, NULL);
		sfRenderWindow_drawCircleShape(window, player1.circle, NULL);
		movetowards(&player1, &ball);

		sfRenderWindow_display(window);
	}


	//done
//	for (int i = 0; i < N; i++)
//		sfCircleShape_destroy(circles[i]);

	sfCircleShape_destroy(ball.circle);
	sfCircleShape_destroy(player1.circle);
	sfRenderWindow_destroy(window);
//	free(circles);

	return 0;
}
