/*
 * lax_cipher.c
 *
 *  Created on: Nov 25, 2017
 *      Author: derkach
 */
#include "ciphers.h"

uint32_t lax_primitive(uint32_t in, const uint32_t *L) {
	uint32_t x, y;
	uint32_t out = 0;
	x = in >> LAX_PART_BIT_LEN;
	y = (in & LAX_PART_BIT_MASK);
	x = (x + y) & LAX_PART_BIT_MASK;
	out = L[x];
	out ^= L[y] << LAX_PART_BIT_LEN;
	return out;
}

void lax_primitive_check(const uint32_t *L) {
	uint32_t block;
	uint32_t lax_f, lax_m;
	uint32_t in;

	INFO("Start check...");
	for (block = 0; block < LAX_SPACE; ++block) {
		in = block;
		lax_f = lax_primitive(block, L);
		if (in != block) {
			ERROR("block mismatch func\n");
		}
		lax_f = lax_primitive(block, L);

		block = in;
		lax_m = LAX_PRIM(block, L);
		if (in != block) {
			ERROR("block mismatch macro\n");
		}

		if (lax_m != lax_f) {
			ERROR("ARX MISMATCH\n");
			printf("in = 0x%08X\n", in);
			printf("ARX_MACRO = 0x%08X\n", lax_m);
			printf("ARX_FUNCK = 0x%08X\n", lax_f);
			getchar();
			getchar();
		}
		if (lax_m >> LAX_BIT_LEN) {
			ERROR("ARX MACRO BIT ERROR\n");
			printf("in = 0x%08X\n", in);
			printf("ARX_MACRO = 0x%08X\n", lax_m);
			getchar();
			getchar();
		}
		if (lax_f >> LAX_BIT_LEN) {
			ERROR("ARX FUNC BIT ERROR\n");
			printf("in = 0x%08X\n", in);
			printf("ARX_MACRO = 0x%08X\n", lax_f);
			getchar();
			getchar();
		}
	}
	INFO("End check...");
}
