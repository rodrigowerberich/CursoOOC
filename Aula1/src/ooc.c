/*
 * ooc.c
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#include <ooc.h>
#include <ooc.r>
#include <ooc_assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#define MAGIC 0x0effaced

// Helpers
static inline bool ooc_is_not_object(const Object_r* self){
	return (!self || (self->magic != MAGIC));
}

void* ooc_new(const void* class_descriptor, ...) {
	const Class_r* class = ooc_cast(Class_d, class_descriptor);
	ASSERT(class, NULL);
	Object_r* object;
	va_list ap;
	ASSERT(class && class->size, NULL);
	object = calloc(1, class->size);
	ASSERT(object, NULL);
	object->magic = MAGIC;
	object->class = class;
	va_start(ap, class_descriptor);
	object = ooc_ctor(object, &ap);
	va_end(ap);
	return object;
}
void* ooc_delete(void* self) {
	if (self) {
		if(ooc_is_not_object(self)){
			free(self);
		}else{
			free(ooc_dtor(self));
		}
	}
	return NULL;
}
// Static linked methods
const void* ooc_classOf(const void* _self){
	const Object_r* self = _self;
	ASSERT(!ooc_is_not_object(self), NULL);
	return self->class;
}
size_t ooc_sizeOf(const void* _self){
	const Class_r* class = ooc_classOf(_self);
	ASSERT(class, 0)
	return class->size;
}
bool ooc_isA(const void* self, const void* class){
	ASSERT(!ooc_is_not_object(self), false);
	return (self && (ooc_classOf(self) == class));
}
bool ooc_isOf(const void* self, const void* class){
	if(self){
		const Class_r* my_class = ooc_classOf(self);
		ASSERT(my_class, false);
		if(class != Object_d){
			while( my_class != class){
				if(my_class != Object_d){
					my_class = ooc_super(my_class);
				}else{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}
void* ooc_cast(const void* class, const void* self){
	ASSERT(ooc_isOf(self, class), NULL);
	return (void*) self;

}
const void* ooc_super(const void* self){
	const Class_r* class = ooc_cast(Class_d, self);
	ASSERT(class && class->super, NULL);
	return class->super;
}


// Dynamic linked methods
void* ooc_ctor(void* _self, va_list* app) {
	const Class_r* class = ooc_cast(Class_d, ooc_classOf(_self));
	ASSERT(class && class->ctor, NULL);
	return class->ctor(_self, app);
}
void* super_ctor(const void* _class, void* _self, va_list* app) {
	const Class_r* superclass = ooc_cast(Class_d, ooc_super(_class));
	ASSERT(_self && superclass && superclass->ctor, NULL)
	return superclass->ctor(_self, app);
}

void* ooc_dtor(void* _self) {
	const Class_r* class = ooc_cast(Class_d, ooc_classOf(_self));
	ASSERT(class && class->dtor, NULL)
	return class->dtor(_self);
}
void* super_dtor(const void* _class, void* _self) {
	const Class_r* superclass = ooc_cast(Class_d, ooc_super(_class));
	ASSERT(_self && superclass && superclass->dtor, NULL)
	return superclass->dtor(_self);
}
int ooc_differ(const void* _self, const void* b) {
	const Class_r* class = ooc_cast(Class_d, ooc_classOf(_self));
	ASSERT(class && class->differ, 0)
	return class->differ(_self, b);
}
int super_differ(const void* _class, const void* _self, const void* b) {
	const Class_r* superclass = ooc_cast(Class_d, ooc_super(_class));
	ASSERT(_self && superclass && superclass->differ, 0)
	return superclass->differ(_self, b);
}
int ooc_putO(const void* _self, FILE* fp) {
	const Class_r* class = ooc_cast(Class_d, ooc_classOf(_self));
	ASSERT(class && class->putO, 0)
	return class->putO(_self, fp);
}
int super_putO(const void* _class, const void* _self, FILE* fp) {
	const Class_r* superclass = ooc_cast(Class_d, ooc_super(_class));
	ASSERT(_self && superclass && superclass->putO, 0)
	return superclass->putO(_self, fp);
}

// Dynamic linked methods implementation
// Object

static void* Object_ctor(void* self, va_list* app){
	return self;
}

static void* Object_dtor(void* self){
	return self;
}

static int Object_differ(const void* self, const void* b){
	return self != b;
}

static int Object_putO(const void* self, FILE* fp){
	const Class_r* class = ooc_classOf(self);
	ASSERT(class, 0);
	return fprintf(fp, "%s at %p\n", class->name, self);
}

// Class

static void* Class_ctor(void* _self, va_list* app){
	Class_r* self = _self;
	const size_t offset = offsetof(struct Class_r, ctor);
	self->name = va_arg(*app, char*);
	self->super = va_arg(*app, Class_r*);
	self->size = va_arg(*app, size_t);
	ASSERT(self->super, NULL);
	memcpy((char*) self + offset, (char*) self->super + offset,
			ooc_sizeOf(self->super) - offset);
	typedef void (*voidf)();
	voidf selector;
	va_list ap;
	va_copy(ap, *app);
	while ((selector = va_arg(ap, voidf))) {
		voidf method = va_arg(ap, voidf);
		if (selector == (voidf) ooc_ctor){
			*(voidf *) &self->ctor = method;
		}else if (selector == (voidf) ooc_dtor){
			*(voidf *) &self->dtor = method;
		}else if (selector == (voidf) ooc_differ){
			*(voidf *) &self->differ = method;
		}else if (selector == (voidf) ooc_putO){
			*(voidf *) &self->putO = method;
		}
	}
	return self;
}

static void* Class_dtor(void* _self){
	Class_r* self = _self;
	printf("%s: cannot destroy class\n", self->name);
	return NULL;
}

// Initialization

static const Class_r object[] = {
		{
				{
						MAGIC,
						object + 1
				},
				"Object",
				object,
				sizeof(Object_r),
				Object_ctor,
				Object_dtor,
				Object_differ,
				Object_putO
		},
		{
				{
						MAGIC,
						object + 1
				},
				"Class",
				object,
				sizeof(Class_r),
				Class_ctor,
				Class_dtor,
				Object_differ,
				Object_putO
		}
};
const void * Object_d = object;
const void * Class_d = object + 1;
