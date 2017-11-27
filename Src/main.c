#include "ciphers.h"
#include "lipmaa_moriai.h"
#include "analyzer.h"

void lipmaa_moriai_test()
{
	/* lipmaa_moriai.c */
//	lipmaa_moriai_check(XDP_8, 16);
	printf("xdp_8 pass\n");
//	lipmaa_moriai_check(XDP_16, 256);
	printf("xdp_16 pass\n");
}

void lipmaa_moriai_test_3()
{
	clock_t c1, c2;

	c1 = clock();
	lipmaa_moriai_3();
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);

	c1 = c2;
	lipmaa_moriai_check_3(XDP_TOTAL, LAX_PART_SPACE);
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
}

/* Diff analysis checks for s-box */
void diff_sbox_test()
{
	arx_diff_search_sbox_two();
//	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
	arx_diff_search_sbox_three();
}

/* Rot analysis checks */
void rot_anal_test()
{
	clock_t c1, c2;

	c1 = clock();
	arx_rotation_search_two();
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);

	c1 = c2;
	arx_rotation_search_three();
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);

	c1 = c2;
	arx_rotation_search_four();
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);

	c1 = c2;
	arx_rotation_search_five();
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);

	c1 = c2;
	arx_rotation_search_six();
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
}

void diff_anal_test()
{
	clock_t c1, c2;
	c1 = clock();

	/* Diff check */
	arx_diff_search_two();
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
	c1 = c2;
	arx_diff_search_three();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
	arx_diff_search_four();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
	arx_diff_search_five();
}

/* Best rot search */
void best_rot_test()
{
	arx_best_rot_two();
	arx_best_rot_three();
	arx_best_rot_four();
	arx_best_rot_five();
	arx_best_rot_six();
}

void lax_analysis(uint32_t r)
{
	clock_t c1, c2;

	arx_lax_check();
	lipmaa_moriai_test_3();

	c1 = clock();
	trail_search_lax(r);
	c2 = clock();
	printf("Calculation done in %0.1f seconds...\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
	c1 = c2;

}

int main(int argc, char *argv[])
{
	int rounds;
	srand(time(NULL));

	/* ARX-GOST checks */
//	arx_gost_check();

	/* LAX checks */
//	arx_lax_check();
	if (argc == 2)
		rounds = atoi(argv[1]);
	else
		rounds = 3;

	printf("rounds = %d\n", (uint32_t)rounds);
	lax_analysis((uint32_t)rounds);

//	lipmaa_moriai_test_3();
	return 0;
}
