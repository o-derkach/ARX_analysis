#include "analyzer.h"

void arx_rotation_search_two() {
	uint32_t block, block_r;
	uint32_t key_1, key_2;
	uint32_t key_1_r, key_2_r;
	uint32_t out, out_r;
	uint32_t rot;
	uint64_t rot_stat;
	uint64_t rot_theor;
	uint64_t sum = 0;
	uint64_t sq = 0;

	char f_name[FILE_PATH_LEN + 20];

	sprintf(f_name, "%s%s%02d%s", FILE_PATH, "rot_2r_", BLOCK_BIT_LEN, ".txt");

	INFO("File name =");
	DEBUG(f_name);

	FILE *f = fopen(f_name, "w");

	INFO("Start counting rotational 2r...");
	for (rot = 1; rot < PART_BIT_LEN; ++rot) {
		fprintf(f, "ROT = %d \n", rot);
		rot_stat = 0;

		for (block = 0; block < BLOCK_SPACE; ++block) {
			for (key_1 = 0; key_1 < KEY_SPACE; ++key_1) {
				for (key_2 = 0; key_2 < KEY_SPACE; ++key_2) {

					out = ARX_GOST(block, key_1, BLOCK_ROT);
					out = ARX_GOST(out, key_2, BLOCK_ROT);
					out = ROT_LO((out & PART_BIT_MASK), rot) | (ROT_LO((out >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					key_1_r = ROT_LO(key_1, rot);
					key_2_r = ROT_LO(key_2, rot);

					block_r = ROT_LO((block & PART_BIT_MASK), rot) | (ROT_LO((block >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					out_r = ARX_GOST(block_r, key_1_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_2_r, BLOCK_ROT);

					if (out == out_r)
						++rot_stat;

				}
			}
		}

		/* Berson's formula * 2^BLOCK_LEN */
		rot_theor = 1 << (BLOCK_BIT_LEN - 2);
		rot_theor += 1 << (PART_BIT_LEN - 2);
		rot_theor += 1 << (PART_BIT_LEN + rot - 2);
		rot_theor += 1 << (BLOCK_BIT_LEN - rot - 2);
		rot_theor = rot_theor * rot_theor;

		if (rot_theor < rot_stat) {
			sq = rot_stat - rot_theor;
		} else {
			sq = rot_theor - rot_stat;
		}
		sq *= sq;
		sum += sq;

		fprintf(f, "\ttheory = %zu (%.6f); real =  %zu (%.6f)\n",
				rot_theor, rot_theor / 65536.0, rot_stat, rot_stat / 65536.0);
		fprintf(f, "\tsq_distance =  %zu (%.6f)\n", sq, sq / 65536.0);
		fprintf(f, "* * * * *\n");
	}
	fprintf(f, "sum = %zu\n", sum);

	fclose(f);
	INFO("End");
}

void arx_rotation_search_three() {
	uint32_t block, block_r;
	uint32_t key_1, key_2, key_3;
	uint32_t key_1_r, key_2_r, key_3_r;
	uint32_t out, out_r;
	uint32_t rot;
	uint64_t rot_stat;
	uint64_t rot_theor;
	double sum = 0;
	double sq = 0;

	char f_name[FILE_PATH_LEN + 20];

	sprintf(f_name, "%s%s%02d%s", FILE_PATH, "rot_3r_", BLOCK_BIT_LEN, ".txt");

	INFO("File name =");
	DEBUG(f_name);

	FILE *f = fopen(f_name, "w");

	INFO("Start counting rotational 3r...");
	for (rot = 1; rot < PART_BIT_LEN; ++rot) {
		fprintf(f, "ROT = %d \n", rot);
		rot_stat = 0;

		for (block = 0; block < BLOCK_SPACE; ++block) {
			for (key_1 = 0; key_1 < KEY_SPACE; ++key_1) {
				for (key_2 = 0; key_2 < KEY_SPACE; ++key_2) {
				for (key_3 = 0; key_3 < KEY_SPACE; ++key_3) {

					out = ARX_GOST(block, key_1, BLOCK_ROT);
					out = ARX_GOST(out, key_2, BLOCK_ROT);
					out = ARX_GOST(out, key_3, BLOCK_ROT);
					out = ROT_LO((out & PART_BIT_MASK), rot) | (ROT_LO((out >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					key_1_r = ROT_LO(key_1, rot);
					key_2_r = ROT_LO(key_2, rot);
					key_3_r = ROT_LO(key_3, rot);

					block_r = ROT_LO((block & PART_BIT_MASK), rot) | (ROT_LO((block >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					out_r = ARX_GOST(block_r, key_1_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_2_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_3_r, BLOCK_ROT);

					if (out == out_r)
						++rot_stat;
				}
				}
			}
		}

		fprintf(f, "\tcount = %zu\n", rot_stat);

		rot_theor = 1 << (BLOCK_BIT_LEN - 2);
		rot_theor += 1 << (PART_BIT_LEN - 2);
		rot_theor += 1 << (PART_BIT_LEN + rot - 2);
		rot_theor += 1 << (BLOCK_BIT_LEN - rot - 2);
		rot_theor = rot_theor * rot_theor * rot_theor;

		/* for third round */
		/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
		rot_stat *= (1 << PART_BIT_LEN);

		if (rot_theor < rot_stat) {
			sq = (double)(rot_stat - rot_theor);
		} else {
			sq = (double)(rot_theor - rot_stat);
		}
		sq /= 16777216.0;
		sq *= sq;
		sum += sq;

		fprintf(f, "\ttheory = %zu (%.6f); real =  %zu (%.6f)\n",
				rot_theor, rot_theor / 16777216.0, rot_stat, (double)rot_stat / 16777216.0);
		fprintf(f, "\tsq_distance =  %.6f\n", sq);
		fprintf(f, "* * * * *\n");
	}
	fprintf(f, "sum = %.6f\n", sum);

	fclose(f);
	INFO("End");
}

void arx_rotation_search_four() {
	uint32_t block, block_r;
	uint32_t key_1, key_2, key_3, key_4;
	uint32_t key_1_r, key_2_r, key_3_r, key_4_r;
	uint32_t out, out_r;
	uint32_t rot;
	double rot_stat;
	double rot_theor;
	double sum = 0;
	double sq = 0;

	char f_name[FILE_PATH_LEN + 20];

	sprintf(f_name, "%s%s%02d%s", FILE_PATH, "rot_4r_", BLOCK_BIT_LEN, ".txt");

	INFO("File name =");
	DEBUG(f_name);

	FILE *f = fopen(f_name, "w");

	INFO("Start counting rotational 4r...");
	for (rot = 1; rot < PART_BIT_LEN; ++rot) {
		fprintf(f, "ROT = %d \n", rot);
		rot_stat = 0;

		for (block = 0; block < BLOCK_SPACE; ++block) {
			for (key_1 = 0; key_1 < KEY_SPACE; ++key_1) {
				for (key_2 = 0; key_2 < KEY_SPACE; ++key_2) {
				for (key_3 = 0; key_3 < KEY_SPACE; ++key_3) {
				for (key_4 = 0; key_4 < KEY_SPACE; ++key_4) {

					out = ARX_GOST(block, key_1, BLOCK_ROT);
					out = ARX_GOST(out, key_2, BLOCK_ROT);
					out = ARX_GOST(out, key_3, BLOCK_ROT);
					out = ARX_GOST(out, key_4, BLOCK_ROT);
					out = ROT_LO((out & PART_BIT_MASK), rot) | (ROT_LO((out >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					key_1_r = ROT_LO(key_1, rot);
					key_2_r = ROT_LO(key_2, rot);
					key_3_r = ROT_LO(key_3, rot);
					key_4_r = ROT_LO(key_4, rot);

					block_r = ROT_LO((block & PART_BIT_MASK), rot) | (ROT_LO((block >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					out_r = ARX_GOST(block_r, key_1_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_2_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_3_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_4_r, BLOCK_ROT);

					if (out == out_r)
						++rot_stat;
				}
				}
				}
			}
		}

		/* count probability */
		rot_stat /= (double)BLOCK_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;

		/* Berson's standard formula */
		rot_theor = 1.0;
		rot_theor += 1.0 / (1 << rot);
		rot_theor += 1.0 / (1 << PART_BIT_LEN);
		rot_theor += 1.0 / (1 << (PART_BIT_LEN - rot));
		rot_theor *= 0.25;
		rot_theor = rot_theor * rot_theor * rot_theor * rot_theor;

		if (rot_theor < rot_stat) {
			sq = (double)(rot_stat - rot_theor);
		} else {
			sq = (double)(rot_theor - rot_stat);
		}
		sum += sq * sq;

		fprintf(f, "\ttheory = %.6f; real = %.6f\n", rot_theor, rot_stat);
		fprintf(f, "\tdistance =  %.6f\n", sq);
		fprintf(f, "\tsq_distance =  %.6f\n", sq * sq);
		fprintf(f, "* * * * *\n");
	}
	fprintf(f, "sum = %.6f\n", sum);

	fclose(f);
	INFO("End");
}

void arx_rotation_search_five() {
	uint32_t block, block_r;
	uint32_t key_1, key_2, key_3, key_4, key_5;
	uint32_t key_1_r, key_2_r, key_3_r, key_4_r, key_5_r;
	uint32_t out, out_r;
	uint32_t rot;
	double rot_stat;
	double rot_theor;
	double sum = 0;
	double sq = 0;

	char f_name[FILE_PATH_LEN + 20];

	sprintf(f_name, "%s%s%02d%s", FILE_PATH, "rot_5r_", BLOCK_BIT_LEN, ".txt");

	INFO("File name =");
	DEBUG(f_name);

	FILE *f = fopen(f_name, "w");

	INFO("Start counting rotational 5r...");
	for (rot = 1; rot < PART_BIT_LEN; ++rot) {
		fprintf(f, "ROT = %d \n", rot);
		rot_stat = 0;

		for (block = 0; block < BLOCK_SPACE; ++block) {
			for (key_1 = 0; key_1 < KEY_SPACE; ++key_1) {
				for (key_2 = 0; key_2 < KEY_SPACE; ++key_2) {
				for (key_3 = 0; key_3 < KEY_SPACE; ++key_3) {
				for (key_4 = 0; key_4 < KEY_SPACE; ++key_4) {
				for (key_5 = 0; key_5 < KEY_SPACE; ++key_5) {

					out = ARX_GOST(block, key_1, BLOCK_ROT);
					out = ARX_GOST(out, key_2, BLOCK_ROT);
					out = ARX_GOST(out, key_3, BLOCK_ROT);
					out = ARX_GOST(out, key_4, BLOCK_ROT);
					out = ARX_GOST(out, key_5, BLOCK_ROT);
					out = ROT_LO((out & PART_BIT_MASK), rot) | (ROT_LO((out >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					key_1_r = ROT_LO(key_1, rot);
					key_2_r = ROT_LO(key_2, rot);
					key_3_r = ROT_LO(key_3, rot);
					key_4_r = ROT_LO(key_4, rot);
					key_5_r = ROT_LO(key_5, rot);

					block_r = ROT_LO((block & PART_BIT_MASK), rot) | (ROT_LO((block >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					out_r = ARX_GOST(block_r, key_1_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_2_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_3_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_4_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_5_r, BLOCK_ROT);

					if (out == out_r)
						++rot_stat;
				}
				}
				}
				}
			}
		}

		/* count probability */
		rot_stat /= (double)BLOCK_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;

		/* Berson's standard formula */
		rot_theor = 1.0;
		rot_theor += 1.0 / (1 << rot);
		rot_theor += 1.0 / (1 << PART_BIT_LEN);
		rot_theor += 1.0 / (1 << (PART_BIT_LEN - rot));
		rot_theor *= 0.25;
		rot_theor = rot_theor * rot_theor * rot_theor * rot_theor * rot_theor;

		if (rot_theor < rot_stat) {
			sq = (double)(rot_stat - rot_theor);
		} else {
			sq = (double)(rot_theor - rot_stat);
		}
		sum += sq * sq;

		fprintf(f, "\ttheory = %.6f; real = %.6f\n", rot_theor, rot_stat);
		fprintf(f, "\tdistance =  %.6f\n", sq);
		fprintf(f, "\tsq_distance =  %.6f\n", sq * sq);
		fprintf(f, "* * * * *\n");
	}
	fprintf(f, "sum = %.6f\n", sum);

	fclose(f);
	INFO("End");
}

void arx_rotation_search_six() {
	uint32_t block, block_r;
	uint32_t key_1, key_2, key_3, key_4, key_5, key_6;
	uint32_t key_1_r, key_2_r, key_3_r, key_4_r, key_5_r, key_6_r;
	uint32_t out, out_r;
	uint32_t rot;
	double rot_stat;
	double rot_theor;
	double sum = 0;
	double sq = 0;

	char f_name[FILE_PATH_LEN + 20];

	sprintf(f_name, "%s%s%02d%s", FILE_PATH, "rot_6r_", BLOCK_BIT_LEN, ".txt");

	INFO("File name =");
	DEBUG(f_name);

	FILE *f = fopen(f_name, "w");

	INFO("Start counting rotational 6r...");
	for (rot = 1; rot < PART_BIT_LEN; ++rot) {
		fprintf(f, "ROT = %d \n", rot);
		rot_stat = 0;

		for (block = 0; block < BLOCK_SPACE; ++block) {
			for (key_1 = 0; key_1 < KEY_SPACE; ++key_1) {
				for (key_2 = 0; key_2 < KEY_SPACE; ++key_2) {
				for (key_3 = 0; key_3 < KEY_SPACE; ++key_3) {
				for (key_4 = 0; key_4 < KEY_SPACE; ++key_4) {
				for (key_5 = 0; key_5 < KEY_SPACE; ++key_5) {
				for (key_6 = 0; key_6 < KEY_SPACE; ++key_6) {

					out = ARX_GOST(block, key_1, BLOCK_ROT);
					out = ARX_GOST(out, key_2, BLOCK_ROT);
					out = ARX_GOST(out, key_3, BLOCK_ROT);
					out = ARX_GOST(out, key_4, BLOCK_ROT);
					out = ARX_GOST(out, key_5, BLOCK_ROT);
					out = ARX_GOST(out, key_6, BLOCK_ROT);
					out = ROT_LO((out & PART_BIT_MASK), rot) | (ROT_LO((out >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					key_1_r = ROT_LO(key_1, rot);
					key_2_r = ROT_LO(key_2, rot);
					key_3_r = ROT_LO(key_3, rot);
					key_4_r = ROT_LO(key_4, rot);
					key_5_r = ROT_LO(key_5, rot);
					key_6_r = ROT_LO(key_6, rot);

					block_r = ROT_LO((block & PART_BIT_MASK), rot) | (ROT_LO((block >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					out_r = ARX_GOST(block_r, key_1_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_2_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_3_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_4_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_5_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_6_r, BLOCK_ROT);

					if (out == out_r)
						++rot_stat;
				}
				}
				}
				}
				}
			}
		}

		/* count probability */
		rot_stat /= (double)BLOCK_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;

		/* Berson's standard formula */
		rot_theor = 1.0;
		rot_theor += 1.0 / (1 << rot);
		rot_theor += 1.0 / (1 << PART_BIT_LEN);
		rot_theor += 1.0 / (1 << (PART_BIT_LEN - rot));
		rot_theor *= 0.25;
		rot_theor = rot_theor * rot_theor * rot_theor * rot_theor * rot_theor * rot_theor;

		if (rot_theor < rot_stat) {
			sq = (double)(rot_stat - rot_theor);
		} else {
			sq = (double)(rot_theor - rot_stat);
		}
		sum += sq * sq;

		fprintf(f, "\ttheory = %.6f; real = %.6f\n", rot_theor, rot_stat);
		fprintf(f, "\tdistance =  %.6f\n", sq);
		fprintf(f, "\tsq_distance =  %.6f\n", sq * sq);
		fprintf(f, "* * * * *\n");
	}
	fprintf(f, "sum = %.6f\n", sum);

	fclose(f);
	INFO("End");
}

void arx_rotation_search_three_recount() {
	uint32_t block, block_r;
	uint32_t key_1, key_2, key_3;
	uint32_t key_1_r, key_2_r, key_3_r;
	uint32_t out, out_r;
	uint32_t rot;
	double rot_stat;
	double rot_theor;
	double sum = 0;
	double sq = 0;

	char f_name[FILE_PATH_LEN + 20];

	sprintf(f_name, "%s%s%02d%s", FILE_PATH, "rot_3rr_", BLOCK_BIT_LEN, ".txt");

	INFO("File name =");
	DEBUG(f_name);

	FILE *f = fopen(f_name, "w");

	INFO("Start counting rotational 3rr...");
	for (rot = 1; rot < PART_BIT_LEN; ++rot) {
		fprintf(f, "ROT = %d \n", rot);
		rot_stat = 0;

		for (block = 0; block < BLOCK_SPACE; ++block) {
			for (key_1 = 0; key_1 < KEY_SPACE; ++key_1) {
				for (key_2 = 0; key_2 < KEY_SPACE; ++key_2) {
				for (key_3 = 0; key_3 < KEY_SPACE; ++key_3) {

					out = ARX_GOST(block, key_1, BLOCK_ROT);
					out = ARX_GOST(out, key_2, BLOCK_ROT);
					out = ARX_GOST(out, key_3, BLOCK_ROT);
					out = ROT_LO((out & PART_BIT_MASK), rot) | (ROT_LO((out >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					key_1_r = ROT_LO(key_1, rot);
					key_2_r = ROT_LO(key_2, rot);
					key_3_r = ROT_LO(key_3, rot);

					block_r = ROT_LO((block & PART_BIT_MASK), rot) | (ROT_LO((block >> PART_BIT_LEN), rot) << PART_BIT_LEN);

					out_r = ARX_GOST(block_r, key_1_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_2_r, BLOCK_ROT);
					out_r = ARX_GOST(out_r, key_3_r, BLOCK_ROT);

					if (out == out_r)
						++rot_stat;
				}
				}
			}
		}

		fprintf(f, "\tcount = %.1f\n", rot_stat);
		/* count probability */
		rot_stat /= (double)BLOCK_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;
		rot_stat /= (double)KEY_SPACE;

		/* Berson's standard formula */
		rot_theor = 1.0;
		rot_theor += 1.0 / (1 << rot);
		rot_theor += 0.0625;
		rot_theor += 1.0 / (1 << (PART_BIT_LEN - rot));
		rot_theor *= 0.25;
		rot_theor = rot_theor * rot_theor * rot_theor;

		if (rot_theor < rot_stat) {
			sq = (double)(rot_stat - rot_theor);
		} else {
			sq = (double)(rot_theor - rot_stat);
		}
		sum += sq * sq;

		fprintf(f, "\ttheory = %.6f; real = %.6f\n", rot_theor, rot_stat);
		fprintf(f, "\tdistance =  %.6f\n", sq);
		fprintf(f, "\tsq_distance =  %.6f\n", sq * sq);
		fprintf(f, "* * * * *\n");
	}
	fprintf(f, "sum = %.6f\n", sum);

	fclose(f);
	INFO("End");
}
