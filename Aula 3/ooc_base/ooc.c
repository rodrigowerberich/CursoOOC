/*
 * ooc.c
 *
 *  Created on: 28 de dez de 2018
 *      Author: lua
 */


#include <ooc.h>
#include <ooc.r>
#include <ooc_assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

/*------------------------------------------------*/
/*-------------- DEFINE HELPERS ------------------*/
/*------------------------------------------------*/
#define MAGIC 0x0effaced
#define TYPE_DECODER_BASE(type_, ap_type_)\
    if(strcmp(name, #type_) == 0){\
        type_* v_aux = malloc(sizeof(type_));\
        *v_aux = va_arg(*app, ap_type_);\
        return v_aux;\
    }
#define TYPE_DECODER(type_) TYPE_DECODER_BASE(type_, type_)


/*------------------------------------------------*/
/*------------------- Helper methods -------------*/
/*------------------------------------------------*/
static inline bool ooc_is_not_object(const Object_r* self){
    return (!self || (self->magic != MAGIC));
}

static void* ooc_v_new_c(const char* name, va_list* app){
    TYPE_DECODER_BASE(char, int);
    TYPE_DECODER(int);
    TYPE_DECODER_BASE(_Bool, int);
    TYPE_DECODER_BASE(uint8_t, int);
    TYPE_DECODER_BASE(uint16_t, int);
    TYPE_DECODER(uint32_t);
    TYPE_DECODER_BASE(int8_t, int);
    TYPE_DECODER_BASE(int16_t, int);
    TYPE_DECODER(int32_t);
    TYPE_DECODER(size_t);
    TYPE_DECODER_BASE(float, double);
    TYPE_DECODER(double);
    return NULL;
}
void* ooc_new_c_(const char* name, ...){
    va_list ap;
    va_start(ap, name);
    void* return_value = ooc_v_new_c(name, &ap);
    va_end(ap);
    return return_value;
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
/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/
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
        if(ooc_is_not_object(self)){
            return false;
        }
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
void* ooc_safeClone(void * self, ...){
    if(ooc_is_not_object(self)){
        va_list ap;
        va_start(ap, self);
        int element_size = va_arg(ap, int);
        va_end(ap);
        return memcpy(malloc(element_size), self, element_size);
    }else{
        return ooc_clone(self);
    }
}
/*-------------------------------------------------*/
/*----------- Dynamic linked methods --------------*/
/*-------------------------------------------------*/
DYNAMIC_METHOD(Class, NULL, M_CTOR);
DYNAMIC_METHOD(Class, NULL, M_DTOR);
DYNAMIC_METHOD(Class, -1,   M_DIFFER);
DYNAMIC_METHOD(Class, -1,   M_PUTO);
DYNAMIC_METHOD(Class, NULL, M_CLONE);
/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
/*-------------------- Object --------------------*/
static OVERWRITE_METHOD(Object, M_CTOR){
    return _self;
}

static OVERWRITE_METHOD(Object, M_DTOR){
    return _self;
}

static OVERWRITE_METHOD(Object, M_DIFFER){
    return _self != _other;
}

static OVERWRITE_METHOD(Object, M_PUTO){
    const Class_r* class = ooc_classOf(_self);
    ASSERT(class, 0);
    return fprintf(fp, "%s at %p\n", class->name, class);
}
static OVERWRITE_METHOD(Object, M_CLONE){
    return _self;
}
/*------------------- Class -------------------*/
static OVERWRITE_METHOD(Class, M_CTOR){
    Class_r* self = _self;
    const size_t offset = offsetof(struct Class_r, ooc_ctor);
    self->name = va_arg(*app, char*);
    self->super = va_arg(*app, Class_r*);
    self->size = va_arg(*app, size_t);
    ASSERT(self->super, NULL);
    memcpy((char*) self + offset, (char*) self->super + offset, ooc_sizeOf(self->super) - offset);
    SELECTOR_LOOP(
        FIRST_SELECTOR(M_CTOR)
        ADD_SELECTOR(M_DTOR)
        ADD_SELECTOR(M_DIFFER)
        ADD_SELECTOR(M_PUTO)
        ADD_SELECTOR(M_CLONE)
    )
}

static OVERWRITE_METHOD(Class, M_DTOR){
    Class_r* self = _self;
    printf("%s: cannot destroy class\n", self->name);
    return NULL;
}
/*-------------------------------*/
/*------- Initialization --------*/
/*-------------------------------*/
static const Class_r object[] = {
        {
                {
                        MAGIC,
                        object + 1
                },
                "Object",
                object,
                sizeof(Object_r),
                Object_ooc_ctor,
                Object_ooc_dtor,
                Object_ooc_differ,
                Object_ooc_clone,
                Object_ooc_putO
        },
        {
                {
                        MAGIC,
                        object + 1
                },
                "Class",
                object,
                sizeof(Class_r),
                Class_ooc_ctor,
                Class_ooc_dtor,
                Object_ooc_differ,
                Object_ooc_clone,
                Object_ooc_putO
        }
};
const void * Object_d = object;
const void * Class_d = object + 1;

const void* initClass(){
    return Class_d;
}
const void* initObject(){
    return Object_d;
}
