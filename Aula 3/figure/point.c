/*
 * point.c
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#include <point.h>
#include <point.r>
#include <ooc_assert.h>
#include <stdarg.h>

// Static linked method
void point_move(o_Point _point, int x, int y){
	CAST(point, Point);
	ASSERT(point, );
	point->x += x;
	point->y += y;

}

// Dynamic linked method
DYNAMIC_METHOD(PointClass, ,M_POINT_DRAW);

// Implementations

static OVERWRITE_METHOD(Point, M_CTOR){
	SUPER_CTOR(self, Point);
	self->x = va_arg(*app, int);
	self->y = va_arg(*app, int);
	return self;
}

static OVERWRITE_METHOD(Point, M_POINT_DRAW){
	CAST(self, Point);
	ASSERT(self, );
	printf("Point at %d,%d\n", self->x, self->y);
}

static OVERWRITE_METHOD(PointClass, M_CTOR){
	SUPER_CTOR(self, PointClass);
	SELECTOR_LOOP(
		FIRST_SELECTOR(M_POINT_DRAW);
	)
}

const void* Point_d;
const void* PointClass_d;

const void* initPointClass(){
	return ooc_new(	ClassClass(),
			"PointClass",
			ClassClass(),
			sizeof(PointClass_r),
			LINK_METHOD(PointClass, M_CTOR),
			0);
}

const void* initPoint(){
	return ooc_new(	PointClassClass(),
			"Point",
			ObjectClass(),
			sizeof(Point_r),
			LINK_METHOD(Point, M_CTOR),
			LINK_METHOD(Point, M_POINT_DRAW),
			0);
}

