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
	CLASS_DYNAMIC_METHOD(M_POINT_DRAW);
}PointClass_r;

SUPER_DYNAMIC_METHOD(M_POINT_DRAW);

#endif /* POINT_R_ */
