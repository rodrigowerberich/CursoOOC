/*
 * point.h
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#ifndef POINT_H_
#define POINT_H_

#include <ooc.h>

CLASS_DECLARATION(Point);
CLASS_DECLARATION(PointClass);

// Static linked method
void point_move(o_Point point, int x, int y);

// Dynamic linked method
#define M_POINT_DRAW_DEF   void, point_draw
#define M_POINT_DRAW_ARG   o_Point _self
#define M_POINT_DRAW_PARAM         _self
DYNAMIC_METHOD_HEADER(M_POINT_DRAW);

#endif /* POINT_H_ */
