/*
 * main.c
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#include <ooc.h>
#include <point.h>
#include <circle.h>

#define CIRCLE

#ifndef CIRCLE
int main(){
	o_Point point= ooc_new(PointClass(), 1, 5);
	point_draw(point);
	point_move(point, 15, 20);
	point_draw(point);
	ooc_delete(point);
	return 0;
}
#endif

#ifdef CIRCLE
int main(){
	o_Point point= ooc_new(PointClass(), 1, 5);
	o_Circle circle = ooc_new(CircleClass(), 7, 9, 3);
	int* p_int = ooc_new_c(int, 9);
	point_draw(point);
	point_draw(circle);
	point_move(point, 15, *p_int);
	point_move(circle, 3, 1);
	point_draw(point);
	point_draw(circle);
	ooc_delete(point);
	ooc_delete(circle);
	ooc_delete(p_int);
	return 0;
}
#endif
