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


static void* Circle_ctor(void* _self, va_list* app){
	Circle_r* self = super_ctor(Circle_d, _self, app);
	self->rad = va_arg(*app, int);
	return self;
}

static void Circle_draw(o_Point _circle){
	Circle_r* circle = ooc_cast(Circle_d, _circle);
	ASSERT(circle, );
	printf("Circle with radius %d at %d,%d\n", circle->rad, circle_x(circle), circle_y(circle));
}

const void* Circle_d;

void initCircle(){
	initPoint();
	if(!Circle_d){
		Circle_d = ooc_new(PointClass_d,
							"Circle",
							Point_d,
							sizeof(Circle_r),
							ooc_ctor, Circle_ctor,
							point_draw, Circle_draw,
							0
		);
	}
}
