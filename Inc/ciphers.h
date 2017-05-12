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

uint32_t arx_gost(uint32_t in, uint32_t k, uint32_t r);

void arx_gost_check();

#endif /* CIPHERS_H_ */
