/*
 * point.h
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#ifndef POINT_H_
#define POINT_H_

#include <ooc.h>

extern const void* Point_d;
typedef void* o_Point;

extern const void* PointClass_d;
typedef void* o_PointClass;

// Static linked method
void point_move(o_Point point, int x, int y);

// Dynamic linked method
void point_draw(o_Point point);

void initPoint();

#endif /* POINT_H_ */
