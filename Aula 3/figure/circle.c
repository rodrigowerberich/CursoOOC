/*
 * circle.c
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#include <circle.h>
#include <circle.r>
#include <stdarg.h>
#include <ooc_assert.h>

// Implementations

static inline int circle_x(Circle_r* circle){
	return ((Point_r*)circle)->x;
}
static inline int circle_y(Circle_r* circle){
	return ((Point_r*)circle)->y;
}


static OVERWRITE_METHOD(Circle, M_CTOR){
	SUPER_CTOR(self, Circle);
	self->rad = va_arg(*app, int);
	return self;
}

static OVERWRITE_METHOD(Circle, M_POINT_DRAW){
	CAST(self, Circle);
	ASSERT(self, );
	printf("Circle with radius %d at %d,%d\n", self->rad, circle_x(self), circle_y(self));
}

const void* Circle_d;

const void* initCircle(){
		return ooc_new(PointClassClass(),
						"Circle",
						PointClass(),
						sizeof(Circle_r),
						LINK_METHOD(Circle, M_CTOR),
						LINK_METHOD(Circle, M_POINT_DRAW),
						0
		);
}
