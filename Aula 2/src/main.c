/*
 * main.c
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#include <ooc.h>
#include <point.h>
#include <circle.h>

//#define CIRCLE

#ifndef CIRCLE
int main(){
	initPoint();
	o_Point point= ooc_new(Point_d, 1, 5);
	point_draw(point);
	point_move(point, 15, 20);
	point_draw(point);
	ooc_delete(point);
	return 0;
}
#endif

#ifdef CIRCLE
int main(){
	initCircle();
	o_Point point= ooc_new(Point_d, 1, 5);
	o_Circle circle = ooc_new(Circle_d, 7, 9, 3);
	point_draw(point);
	point_draw(circle);
	point_move(point, 15, 20);
	point_move(circle, 3, 1);
	point_draw(point);
	point_draw(circle);
	ooc_delete(point);
	ooc_delete(circle);
	return 0;
}
#endif
