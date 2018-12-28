/*
 * ooc_macros.h
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#ifndef OOC_MACROS_H_
#define OOC_MACROS_H_

#define ARG(...) __VA_ARGS__

#define DYNAMIC_METHOD_BODY(class_, method_, return_, ...)\
	const class_##_r* class = ooc_cast(class_##Class(), ooc_classOf(_self));\
	ASSERT(class && class->method_, return_); \
	return class->method_(__VA_ARGS__);

#define DYNAMIC_METHOD_IMP_(class_, error_return_, return_type_, method_, _arguments, _parameters)\
        return_type_ method_(_arguments){\
			DYNAMIC_METHOD_BODY(class_, method_, error_return_, _parameters)\
		}\

#define DYNAMIC_METHOD_IMP(class_, error_return_, def_, parameter_)\
		DYNAMIC_METHOD_IMP__(class_, error_return_, def_, ARG(parameter_))

#define SUPER_METHOD_BODY(class_, method_, error_return_, ...)\
		const class_##_r* superclass = ooc_cast(class_##Class(), ooc_super(_class));\
		ASSERT(_self && superclass && superclass->method_, error_return_);\
		return superclass->method_(__VA_ARGS__);

#define SUPER_METHOD_IMP_(class_, error_return_, return_type_, method_, _arguments, _parameters)\
        return_type_ super_##method_(const void* _class, _arguments){\
			SUPER_METHOD_BODY(class_, method_, error_return_, _parameters)\
		}\

#define SUPER_METHOD_IMP(class_, error_return_, def_, parameter_)\
		SUPER_METHOD_IMP_(class_, error_return_, def_, ARG(parameter_))

#define DYNAMIC_METHOD__(class_, error_return_, def_, arg_,parameters_)\
		DYNAMIC_METHOD_IMP_(class_, error_return_, def_, ARG(arg_), ARG(parameters_))\
		SUPER_METHOD_IMP_(class_, error_return_, def_, ARG(arg_), ARG(parameters_))

#define DYNAMIC_METHOD_(class_, error_return_, def_, args_, parameters_)\
		DYNAMIC_METHOD__(class_, error_return_, ARG(def_), ARG(args_), ARG(parameters_));
#define DYNAMIC_METHOD(class_, error_return_, name_) DYNAMIC_METHOD_(class_, error_return_, ARG(name_##_DEF), ARG(name_##_ARG), ARG(name_##_PARAM))

#define SELECTOR_LOOP(body_)\
		typedef void (*voidf)();\
		voidf selector;\
		va_list ap;\
		va_copy(ap, *app);\
		while ((selector = va_arg(ap, voidf))) {\
			voidf method = va_arg(ap, voidf);\
			body_\
		}\
		return self;
#define SELECTOR(name_) (selector == (voidf) name_)	{*(voidf *) &self->name_ = method;}
#define FIRST_SELECTOR__(ignore_, name_) if SELECTOR(name_)
#define FIRST_SELECTOR_(expand_) FIRST_SELECTOR__(expand_)
#define FIRST_SELECTOR(def_) FIRST_SELECTOR_(def_##_DEF)
#define ADD_SELECTOR__(ignore_, name_) else if SELECTOR(name_)
#define ADD_SELECTOR_(expand_) ADD_SELECTOR__(expand_)
#define ADD_SELECTOR(def_) ADD_SELECTOR_(def_##_DEF)

#define LINK_METHOD__(class_, ignore_, name_)  name_, class_##_##name_
#define LINK_METHOD_(class_, expand_) LINK_METHOD__(class_, expand_)
#define LINK_METHOD(class_, def_) LINK_METHOD_(class_, def_##_DEF)

#define SUPER_CTOR(out, class_) class_##_r* out = super_ooc_ctor(class_##Class(), _##out, app)
#define SUPER_DTOR(out, class_) class_##_r* out = super_ooc_dtor(class_##Class(), _##out)
#define CAST(out, class_) class_##_r* out = ooc_cast(class_##Class(), _ ## out);

#define DYNAMIC_METHOD_HEADER__(return_, name_, ...) return_ name_(__VA_ARGS__)
#define DYNAMIC_METHOD_HEADER_(x1,x2) DYNAMIC_METHOD_HEADER__(x1,x2)
#define DYNAMIC_METHOD_HEADER(x) DYNAMIC_METHOD_HEADER_(ARG(x ##_DEF), ARG(x ##_ARG))
#define CLASS_DYNAMIC_METHOD__(return_, name_, ...) return_ (*name_)(__VA_ARGS__)
#define CLASS_DYNAMIC_METHOD_(x1,x2) CLASS_DYNAMIC_METHOD__(x1,x2)
#define CLASS_DYNAMIC_METHOD(x) CLASS_DYNAMIC_METHOD_(ARG(x ##_DEF), ARG(x ##_ARG))
#define SUPER_DYNAMIC_METHOD__(return_, name_, ...) return_ super_##name_(const void* _class, __VA_ARGS__)
#define SUPER_DYNAMIC_METHOD_(x1, x2) SUPER_DYNAMIC_METHOD__(x1, x2)
#define SUPER_DYNAMIC_METHOD(x) SUPER_DYNAMIC_METHOD_(ARG(x ##_DEF), ARG(x ##_ARG))

#define OVERWRITE_METHOD__(class_, return_, name_, ...)\
return_ class_##_##name_(__VA_ARGS__)
#define OVERWRITE_METHOD_(class_, def_, args_) OVERWRITE_METHOD__(class_, def_, args_)
#define OVERWRITE_METHOD(class_, name_) OVERWRITE_METHOD_(class_, ARG(name_##_DEF), ARG(name_##_ARG))

#define CLASS_DECLARATION(name_)\
        extern const void* name_##_d;\
        typedef void* o_##name_;\
        const void* init##name_();\
        static inline const void* name_##Class(){\
            if(!name_##_d){\
                name_##_d = init##name_();\
            }\
            return name_##_d;\
        }



#endif /* OOC_MACROS_H_ */
