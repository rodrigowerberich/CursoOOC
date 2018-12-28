/*
 * object.h
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#ifndef OOC_H_
#define OOC_H_

#include <stdio.h>
#include <stdbool.h>

// Descriptors
extern const void* Object_d;
typedef void* o_Object;

extern const void* Class_d;
typedef void* o_Class;

// Helpers
void* ooc_new(const void* class_descriptor, ...);
void* ooc_delete(void* self);

// Static linked methods
const void* ooc_classOf(const void* self);
size_t ooc_sizeOf(const void* self);
bool ooc_isA(const void* self, const void* class);
bool ooc_isOf(const void* self, const void* class);
void* ooc_cast(const void* class, const void* self);
const void* ooc_super(const void* self);



// Dynamic linked methods
void* ooc_ctor(void* self, va_list* app);
void* ooc_dtor(void* self);
int ooc_differ(const void* self, const void* b);
int ooc_putO(const void* self, FILE* fp);

#endif /* OOC_H_ */
