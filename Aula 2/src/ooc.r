/*
 * ooc.r
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#ifndef OOC_R_
#define OOC_R_

#include <stdint.h>

typedef struct Object_r{
	uint32_t magic;
	const struct Class_r* class;
} Object_r;

typedef struct Class_r{
	 const Object_r _;
	 const char* name;
	 const struct Class_r* super;
	 size_t size;
	 void* (*ctor)(void* self, va_list* app);
	 void* (*dtor)(void* self);
	 int   (*differ)(const void* self, const void* b);
	 int   (*putO)(const void* self, FILE* fp);
} Class_r;

void* super_ctor(const void* class, void* self, va_list* app);
void* super_dtor(const void* class, void* self);
int  super_differ(const void* class, const void* self, const void* b);
int  super_putO(const void* class, const void* self, FILE* fp);

#endif /* OOC_R_ */
