/*
 * point.r
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#ifndef POINT_R_
#define POINT_R_

#include <ooc.r>

typedef struct Point_r{
	const Object_r _;
	int x;
	int y;
} Point_r;

typedef struct PointClass_r{
	const Class_r _;
	void (*point_draw)(o_Point point);
}PointClass_r;

void super_point_draw(const void* class, o_Point point);

#endif /* POINT_R_ */
