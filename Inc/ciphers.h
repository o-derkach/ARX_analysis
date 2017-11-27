/*
 * ciphers.h
 *
 *  Created on: May 12, 2017
 *      Author: derkach
 */

#ifndef CIPHERS_H_
#define CIPHERS_H_

#include "config.h"
#include "utils.h"

#define ROT_HI(A, R) (((A << R) | (A >> (PART_BIT_LEN - R))) & PART_BIT_MASK)
#define ROT_LO(A, R) (((A << (PART_BIT_LEN - R)) & PART_BIT_MASK) | (A >> R))

#define ARX_GOST(X, K, R) ((X & PART_BIT_MASK) << PART_BIT_LEN) | ((X >> PART_BIT_LEN) ^ ROT_HI(((X + K) & PART_BIT_MASK), R))
#define LAX_PRIM(X, L) (L[(X & LAX_PART_BIT_MASK)] << LAX_PART_BIT_LEN) | (L[((X >> LAX_PART_BIT_LEN) + (X & LAX_PART_BIT_MASK)) & LAX_PART_BIT_MASK])
#define LAX_PRIM_WITHOUT(X) (L_box_5[(X & LAX_PART_BIT_MASK)] << LAX_PART_BIT_LEN) | (L_box_5[((X >> LAX_PART_BIT_LEN) + (X & LAX_PART_BIT_MASK)) & LAX_PART_BIT_MASK])

uint32_t arx_gost(uint32_t in, uint32_t k, uint32_t r);

void arx_gost_check();

uint32_t lax_primitive(uint32_t in, const uint32_t *L);

void lax_primitive_check(const uint32_t *L);

#endif /* CIPHERS_H_ */
