#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <CSFML/Graphics.h>

#define GRAY (sfColor){77, 77, 77, 255}
#define GREEN (sfColor){55, 255, 155, 255}
#define RED (sfColor){255,12,123, 255}
#define N 1
#define RADIUS 30.0


typedef struct circle {
	int num;
	sfCircleShape* circle;
	float radius;
	sfColor color;

	float sx;
	float sy;

	bool selected;
} Circle;

void initcircle(Circle* c, int num, sfVector2f pos, float radius, sfColor color) {
	c->num = num;
	c->circle = sfCircleShape_create();
	c->radius = radius;
	c->color = color;
	c->selected = false;
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

	if (sfCircleShape_getPosition(a->circle).x + a->radius > W) {
			sfCircleShape_setPosition(a->circle, (sfVector2f){W - a->radius, sfCircleShape_getPosition(a->circle).y});
//			a->sx = 0.0;
			a->sx = -1.0 * a->sx;
	}
	else if (sfCircleShape_getPosition(a->circle).x - a->radius < 0.0) {
			sfCircleShape_setPosition(a->circle, (sfVector2f){a->radius, sfCircleShape_getPosition(a->circle).y});
			//a->sx = 0.0;
			a->sx = -1.0 * a->sx;
	}

	if (sfCircleShape_getPosition(a->circle).y + a->radius > H) {
			sfCircleShape_setPosition(a->circle, (sfVector2f){sfCircleShape_getPosition(a->circle).x, H - a->radius});
		//	a->sy = 0.0;
			a->sy = -1.0 * a->sy;
	}
	else if (sfCircleShape_getPosition(a->circle).y - a->radius < 0.0) {
			sfCircleShape_setPosition(a->circle, (sfVector2f){sfCircleShape_getPosition(a->circle).x, a->radius});
		//	a->sy = 0.0;
			a->sy = -1.0 * a->sy;
	}


	printf("POS: (%f, %f)\tSPEED: (%f, %f)\n", sfCircleShape_getPosition(a->circle).x + a->radius, sfCircleShape_getPosition(a->circle).y, a->sx, a->sy);

}


void movetowards(Circle* a, Circle* b) {
		sfFloatRect aBounds = sfCircleShape_getGlobalBounds(a->circle);
        sfFloatRect bBounds = sfCircleShape_getGlobalBounds(b->circle);
		if (!sfFloatRect_intersects(&aBounds, &bBounds, NULL)) {
		}
		else if (sfFloatRect_intersects(&aBounds, &bBounds, NULL)) {
				b->sx = a->sx;
				a->sx = -1.0 * b->sx;
//				a->sx = -0.01 * b->sx * a->radius;

				b->sy = a->sy;
				a->sy = -1.0 * b->sy;
//				a->sy = -0.01 * b->sy * a->radius;
		}

//		printf("a: %.6f, b: %.6f\n", a->sx, b->sx);

}

int main() {
	
	sfVideoMode desk = sfVideoMode_getDesktopMode();
	const unsigned int deskx = desk.size.x;
	const unsigned int desky = desk.size.y;

	const unsigned int W = deskx / 3;
	const unsigned int H = desky / 2;

	sfRenderWindow* window = sfRenderWindow_create((const sfVideoMode){{W, H}, 32}, "SFML window", sfNone, sfWindowed, NULL);
	if (!window)
		return -1;

	sfRenderWindow_setPosition(window, (sfVector2i){(deskx / 2) - (W / 2), (desky / 2) - (H / 2)});

	Circle circles[11];

	for (int i = 0; i < 11; i++) {
					initcircle(&circles[i], i, (sfVector2f){W * i / 11, H * i / 11}, 30.0, GREEN);
	}
	circles[2].selected = true;

	Circle* active = &circles[2];

//	Circle p0;
//	initcircle(&p0, '0', (sfVector2f){W * 1.0 / 4.0, H / 5.0}, 30.0, GREEN);
//	Circle p1;
//	initcircle(&p1, '1', (sfVector2f){W * 2.0 / 4.0, H / 4.0}, 30.0, GREEN);
//	Circle p2;
//	initcircle(&p2, '2', (sfVector2f){W * 3.0 / 4.0, H / 3.0}, 30.0, GREEN);
//	Circle p3;
//	initcircle(&p3, '3', (sfVector2f){W * 4.0 / 4.0, H / 2.0}, 30.0, GREEN);
//	Circle p4;
//	initcircle(&p4, '4', (sfVector2f){W * 3.5 / 4.0, H / 1.0}, 30.0, GREEN);

//	Circle b0;
//	initcircle(&b0, '1', (sfVector2f){W / 3.0, H / 2.0}, 15.0, RED);

	

	sfEvent event;
	while (sfRenderWindow_isOpen(window)) {	

		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
			if (event.type == sfEvtKeyPressed) {
				switch (event.key.code) {
					case (sfKeyEscape):
						sfRenderWindow_close(window);
						break;
					case (sfKeyQ):
						sfRenderWindow_close(window);
						break;
					case (sfKeyLControl && sfKeyC):
						sfRenderWindow_close(window);
 						break;
					case (sfKeyTab):
						int tmp = active->num;
						circles[tmp].selected = false;
						if (tmp == 10)
										tmp = 0;
						else 
										tmp += 1;
						circles[tmp].selected = true;
					case (sfKeyH):
						active->sx -= 0.1;
//						sfCircleShape_move(circles[0], (sfVector2f){-10.0, 0.0});
						break;
					case (sfKeyJ):
						active->sy += 0.1;
//						sfCircleShape_move(circles[0], (sfVector2f){0.0, 10.0});
						break;
					case (sfKeyK):
						active->sy -= 0.1;
//						sfCircleShape_move(circles[0], (sfVector2f){0.0, -10.0});
						break;
					case (sfKeyL):
//						sfCircleShape_move(circles[0], (sfVector2f){10.0, 0.0});
						active->sx += 0.1;
						break;
					default:
						break;
				}
			}
		}

		sfRenderWindow_clear(window, GRAY);

//		sfRenderWindow_drawCircleShape(window, p0.circle, NULL);
//		sfRenderWindow_drawCircleShape(window, p1.circle, NULL);
//		sfRenderWindow_drawCircleShape(window, p2.circle, NULL);
//		sfRenderWindow_drawCircleShape(window, p3.circle, NULL);
//		sfRenderWindow_drawCircleShape(window, p4.circle, NULL);
//		sfRenderWindow_drawCircleShape(window, b0.circle, NULL);

	for (int i = 0; i < 11; i++) {
					if (circles[i].selected == true) {
									active = &circles[i];
									sfCircleShape_setFillColor(circles[i].circle, RED);
					}
					else
									sfCircleShape_setFillColor(circles[i].circle,GREEN);
	}

		for (int i = 0; i < 11; i++) {
						sfRenderWindow_drawCircleShape(window, circles[i].circle, NULL);
		}

//		movecircle(&b0, W, H);
//		movecircle(&p0, W, H);
//		movecircle(&p1, W, H);
//		movecircle(&p2, W, H);
//		movecircle(&p3, W, H);
//		movecircle(&p4, W, H);

		for (int i = 0; i < 11; i++) {
//						movecircle(&circles[i], W, H);
		}

// 		movetowards(&b0, &p0);
// 		movetowards(&b0, &p1);
// 		movetowards(&b0, &p2);
// 		movetowards(&b0, &p3);
// 		movetowards(&b0, &p4);

		for (int i = 0; i < 11; i++) {
//						movetowards(active, &b0);
		}

		sfRenderWindow_display(window);
	}


//	sfCircleShape_destroy(p0.circle);
//	sfCircleShape_destroy(p1.circle);
//	sfCircleShape_destroy(p2.circle);
//	sfCircleShape_destroy(p3.circle);
//	sfCircleShape_destroy(p4.circle);
//	sfCircleShape_destroy(b0.circle);

	for (int i = 0; i < 11; i++) {
					sfCircleShape_destroy(circles[i].circle);
	}

	sfRenderWindow_destroy(window);

	return 0;
}
