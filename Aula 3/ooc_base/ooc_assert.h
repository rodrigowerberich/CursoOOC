/*
 * ooc_assert.h
 *
 *  Created on: 27 de dez de 2018
 *      Author: lua
 */

#ifndef OOC_ASSERT_H_
#define OOC_ASSERT_H_

#define ASSERT(assertion_, return_value_) if(!(assertion_)) { printf("ERROR!!!! at %s, line %d from %s\n", __func__, __LINE__, __FILE__); return return_value_;}

#endif /* OOC_ASSERT_H_ */
