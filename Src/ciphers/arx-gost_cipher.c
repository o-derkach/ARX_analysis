#include "ciphers.h"

uint32_t arx_gost(uint32_t in, uint32_t k, uint32_t r) {
	uint32_t x, y;
	uint32_t out = 0;
	x = in >> PART_BIT_LEN;
	y = (in & PART_BIT_MASK);
	out = y << PART_BIT_LEN;
	y = ((y + k) & PART_BIT_MASK);
	y = ROT_HI(y, r);
	y ^= x;
	out ^= y;
	return out;
}

void arx_gost_check() {
	uint32_t block;
	uint32_t key_1, key_2, key_3;
	uint32_t arx_f, arx_m;
	uint32_t in, k;

	INFO("Start check...");
	for (block = 0; block < BLOCK_SPACE; ++block) {
		for (key_1 = 0; key_1 < KEY_SPACE; ++key_1) {
			for (key_2 = 0; key_2 < KEY_SPACE; ++key_2) {
//				for(key_3 = 0; key_3 < KEY_SPACE; ++key_3) {
				in = block;
				k = key_1;

				arx_f = arx_gost(block, key_1, BLOCK_ROT);
				if (k != key_1) {
					ERROR("key_1 mismatch func\n");
				}
				if (in != block) {
					ERROR("block mismatch func\n");
				}
				k = key_2;
				arx_f = arx_gost(arx_f, key_2, BLOCK_ROT);
				if (k != key_2) {
					ERROR("key_2 mismatch func\n");
				}
//				k = key_3;
//				arx_f = arx_gost(arx_f, key_3, BLOCK_ROT);
//				if (k != key_3) {
//					ERROR("key_3 mismatch func\n");
//				}
				k = key_1;
				block = in;
				arx_m = ARX_GOST(block, key_1, BLOCK_ROT);
				if (k != key_1) {
					ERROR("key_1 mismatch macro\n");
				}
				if (in != block) {
					ERROR("block mismatch macro\n");
				}
				k = key_2;
				arx_m = ARX_GOST(arx_m, key_2, BLOCK_ROT);
				if (k != key_2) {
					ERROR("key_2 mismatch macro\n");
				}
//				k = key_3;
//				arx_m = ARX_GOST(arx_m, key_3, BLOCK_ROT);
//				if (k != key_3) {
//					ERROR("key_3 mismatch macro\n");
//				}
				if (arx_m != arx_f) {
					ERROR("ARX MISMATCH\n");
					printf("in = 0x%08X\n", in);
					printf("key_1 = 0x%08X\n", key_1);
					printf("key_2 = 0x%08X\n", key_2);
					printf("ARX_MACRO = 0x%08X\n", arx_m);
					printf("ARX_FUNCK = 0x%08X\n", arx_f);
					getchar();
					getchar();
				}
				if (arx_m >> BLOCK_BIT_LEN) {
					ERROR("ARX MACRO BIT ERROR\n");
					printf("in = 0x%08X\n", in);
					printf("key_1 = 0x%08X\n", key_1);
					printf("key_2 = 0x%08X\n", key_2);
					printf("ARX_MACRO = 0x%08X\n", arx_m);
					getchar();
					getchar();
				}
				if (arx_f >> BLOCK_BIT_LEN) {
					ERROR("ARX FUNC BIT ERROR\n");
					printf("in = 0x%08X\n", in);
					printf("key_1 = 0x%08X\n", key_1);
					printf("key_2 = 0x%08X\n", key_2);
					printf("ARX_MACRO = 0x%08X\n", arx_f);
					getchar();
					getchar();
//				}
				}
			}
		}
	}
	INFO("End check...");
}
