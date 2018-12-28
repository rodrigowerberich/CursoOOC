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
	Point_r* point = ooc_cast(Point_d, _point);
	ASSERT(point, );
	point->x += x;
	point->y += y;

}

// Dynamic linked method
void point_draw(o_Point _self){
	const PointClass_r* class = ooc_cast(PointClass_d, ooc_classOf(_self));
	ASSERT(class && class->point_draw, );
	return class->point_draw(_self);
}
void super_point_draw(const void* _class, o_Point _self) {
	const PointClass_r* superclass = ooc_cast(PointClass_d, ooc_super(_class));
	ASSERT(_self && superclass && superclass->point_draw,)
	return superclass->point_draw(_self);
}

// Implementations

static void* Point_ctor(void* _self, va_list* app){
	Point_r* self = super_ctor(Point_d, _self, app);
	self->x = va_arg(*app, int);
	self->y = va_arg(*app, int);
	return self;
}

static void Point_draw(o_Point _point){
	Point_r* point = ooc_cast(Point_d, _point);
	ASSERT(point, );
	printf("Point at %d,%d\n", point->x, point->y);
}

static void* PointClass_ctor(void* _self, va_list* app){
	PointClass_r* self = super_ctor(PointClass_d, _self, app);
	typedef void (*voidf)();
	voidf selector;
	va_list ap;
	va_copy(ap, *app);
	while ((selector = va_arg(ap, voidf))) {
		voidf method = va_arg(ap, voidf);
		if (selector == (voidf) point_draw){
			*(voidf *) &self->point_draw = method;
		}
	}
	printf("Laco terminou\n");
	return self;
}

const void* Point_d;
const void* PointClass_d;

void initPoint(){
	if(!PointClass_d){
		printf("E ai?\n");
		printf("ooc_ctor: %p\n", ooc_ctor);
		printf("PointClass_ctor: %p\n", PointClass_ctor);
		PointClass_d = ooc_new(	Class_d,
							"PointClass",
							Class_d,
							sizeof(PointClass_r),
							ooc_ctor, PointClass_ctor,
							0);
	}
	if(!Point_d){
		printf("E ai 2?\n");
		printf("ooc_ctor: %p\n", ooc_ctor);
		printf("PointClass_ctor: %p\n", PointClass_ctor);
		printf("point_draw: %p\n", point_draw);
		printf("Point_draw: %p\n", Point_draw);
		Point_d = ooc_new(	PointClass_d,
						"Point",
						Object_d,
						sizeof(Point_r),
						ooc_ctor, Point_ctor,
						point_draw, Point_draw,
						0);
	}
}

