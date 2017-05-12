#include "lipmaa_moriai.h"

static const uint32_t byteWeight[256] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};

void lipmaa_moriai() {
	uint32_t alpha, gamma;
	uint32_t eq;

	char f_name[FILE_PATH_LEN + 15];

	sprintf(f_name, "%s%s%02d%s", file_path, "xdp_", BLOCK_BIT_LEN, ".txt");

	FILE *f = fopen(f_name, "w");

	switch (BLOCK_BIT_LEN) {
		case 8:
			fprintf(f, "static const uint32_t XDP_8[16][16] = {\n");
			break;
		case 16:
			fprintf(f, "static const uint32_t XDP_16[256][256] = {\n");
			break;
		default:
			fclose(f);
			return;
	}

	for (alpha = 0; alpha < KEY_SPACE; ++alpha) {
		fprintf(f, "\t{");
		for (gamma = 0; gamma < KEY_SPACE; ++gamma) {
			eq = (PART_BIT_MASK ^ (alpha << 1)) & (PART_BIT_MASK ^ (gamma << 1)) & PART_BIT_MASK;
			if ((eq & (alpha ^ gamma ^ (gamma << 1)) & PART_BIT_MASK) == 0) {
				fprintf(f, "%5d, ", 1 << (2 * KEY_BIT_LEN - byteWeight[(~eq) & PART_BIT_MASK]));
			}
			else {
				fprintf(f, "    0, ");
			}
		}
		fprintf(f, "},\n");
	}
	fprintf(f, "};\n");

	fclose(f);
}

void lipmaa_moriai_check(const uint32_t xdp[256][256], const uint32_t space) {
	uint32_t in, key, out, out_g;
	uint32_t alpha, gamma;
	uint32_t gamma_arr[256];
	uint32_t i;

	for (alpha = 0; alpha < space; ++alpha) {
		for (i = 0; i < space; ++i)
			gamma_arr[i] = 0;

		for (in = 0; in < space; ++in) {
			for (key = 0; key < space; ++key) {
				out = (in + key) & (space - 1);
				out_g = ((in ^ alpha) + key) & (space - 1);
				gamma = out ^ out_g;
				gamma_arr[gamma]++;
			}
		}

		for (i = 0; i < space; ++i)
			if (gamma_arr[i] != xdp[alpha][i]) {
				ERROR("MISMATCH Lipmaa Moriai!!!\n");
				printf("xdp = %d, gamma_arr = %d\n", xdp[alpha][i], gamma_arr[i]);
				printf("alpha = %d, gamma = %d\n", alpha, i);
				getchar();
				getchar();
			}
	}
}
