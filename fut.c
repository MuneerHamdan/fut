#include <CSFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GRAY (sfColor){77, 77, 77, 255}
#define GREEN (sfColor){55, 255, 155, 255}

#define N 1
#define RADIUS 30.0


typedef struct circle {
	char num;
	sfCircleShape* circle;
	float radius;
	sfColor color;

	float sx;
	float sy;
} Circle;

void initcircle(Circle* c, char num, sfVector2f pos, float radius, sfColor color) {
	c->num = num;
	c->circle = sfCircleShape_create();
	c->radius = radius;
	c->color = color;
	sfCircleShape_setRadius(c->circle, radius);
	sfCircleShape_setOrigin(c->circle, (sfVector2f){radius, radius});
	sfCircleShape_setPosition(c->circle, pos);
	sfCircleShape_setFillColor(c->circle, color);

	c->sx = 0.0;
	c->sy = 0.0;
}

void movecircle(Circle* a, int W, int H) {
	sfCircleShape_move(a->circle, (sfVector2f){a->sx, a->sy});
	if (a->sx > 0.0) {
			a->sx -= 0.00001;
	}
	else if (a->sx < 0.0) {
			a->sx += 0.00001;
	}
	else {
			a->sx = 0.000000;
	}

	if (a->sy > 0.0) {
			a->sy -= 0.00001;
	}
	else if (a->sy < 0.0) {
			a->sy += 0.00001;
	}
	else {
			a->sy = 0.000000;
	}

	if (sfCircleShape_getPosition(a->circle).x + a->radius > W)
			sfCircleShape_setPosition(a->circle, (sfVector2f){W - a->radius, sfCircleShape_getPosition(a->circle).y});
	else if (sfCircleShape_getPosition(a->circle).x - a->radius < W)
			sfCircleShape_setPosition(a->circle, (sfVector2f){W - W + a->radius, sfCircleShape_getPosition(a->circle).y});

	printf("posx: %f, y: %f\n", sfCircleShape_getPosition(a->circle).x + a->radius, sfCircleShape_getPosition(a->circle).y);

}


void movetowards(Circle* a, Circle* b) {
		sfFloatRect aBounds = sfCircleShape_getGlobalBounds(a->circle);
        sfFloatRect bBounds = sfCircleShape_getGlobalBounds(b->circle);
		if (!sfFloatRect_intersects(&aBounds, &bBounds, NULL)) {
		}
		else if (sfFloatRect_intersects(&aBounds, &bBounds, NULL)) {
				b->sx = 0.01;
				a->sx = 0.0;
		}

//		printf("a: %.6f, b: %.6f\n", a->sx, b->sx);

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


	Circle ball;
//	initcircle(&ball, '0', (sfVector2f){W / 2.0, H / 2.0}, 15.0, (sfColor){255,12,123, 255});
	initcircle(&ball, '0', (sfVector2f){W / 3.0, H / 2.0}, 15.0, (sfColor){255,12,123, 255});

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
						player1.sx -= 0.1;
//						sfCircleShape_move(circles[0], (sfVector2f){-10.0, 0.0});
						break;
					case (sfKeyJ):
						player1.sy += 0.1;
//						sfCircleShape_move(circles[0], (sfVector2f){0.0, 10.0});
						break;
					case (sfKeyK):
						player1.sy -= 0.1;
//						sfCircleShape_move(circles[0], (sfVector2f){0.0, -10.0});
						break;
					case (sfKeyL):
//						sfCircleShape_move(circles[0], (sfVector2f){10.0, 0.0});
						player1.sx += 0.1;
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
		movecircle(&player1, W, H);
		movecircle(&ball, W, H);

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
