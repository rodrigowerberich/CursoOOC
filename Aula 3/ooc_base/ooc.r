/*
 * ooc.r
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#ifndef OOC_R_
#define OOC_R_

#include <stdint.h>
#include <ooc.h>

typedef struct Object_r {
    uint32_t              magic;    // magic number to show that this is an object
    const struct Class_r* class;    // object's description
} Object_r;

typedef struct Class_r {
    const Object_r        _;       // class' description
    const char*           name;    // class' name
    const struct Class_r* super;   // class' super class
    size_t                size;    // class' object's size
    CLASS_DYNAMIC_METHOD(M_CTOR);
    CLASS_DYNAMIC_METHOD(M_DTOR);
    CLASS_DYNAMIC_METHOD(M_DIFFER);
    CLASS_DYNAMIC_METHOD(M_CLONE);
    CLASS_DYNAMIC_METHOD(M_PUTO);
} Class_r;

SUPER_DYNAMIC_METHOD(M_CTOR);
SUPER_DYNAMIC_METHOD(M_DTOR);
SUPER_DYNAMIC_METHOD(M_DIFFER);
SUPER_DYNAMIC_METHOD(M_CLONE);
SUPER_DYNAMIC_METHOD(M_PUTO);

#endif /* OOC_R_ */
