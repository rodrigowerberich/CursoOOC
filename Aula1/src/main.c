/*
 * main.c
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#include <ooc.h>

int main(){
	o_Object object = ooc_new(Object_d);
	o_Object object1 = ooc_new(Object_d);
	ooc_putO(object, stdout);
	printf("Are they different 1? %d\n",ooc_differ(object, object1));
	printf("Are they different 0? %d\n",ooc_differ(object, object));
	object = ooc_delete(object);
	return 0;
}
