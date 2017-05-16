#include "ciphers.h"
#include "lipmaa_moriai.h"
#include "analyzer.h"

int main()
{
	srand(time(NULL));
	clock_t c;
	c = clock();
	/* lipmaa_moriai.c */
//	lipmaa_moriai_check(XDP_8, 16);
//	printf("xdp_8 pass\n");
//	lipmaa_moriai_check(XDP_16, 256);
//	printf("xdp_16 pass\n");

	/* ARX-GOST checks */
//	arx_gost_check();

	/* Diff analysis checks */
//	arx_diff_search_sbox_two();
//	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
//	arx_diff_search_sbox_three();

	/* Rot analysis checks */
//	arx_rotation_search_two();
//	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
//	arx_rotation_search_three();
//	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
//	arx_rotation_search_four();
//	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
//	arx_rotation_search_five();
//	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
//	arx_rotation_search_six();

	/* Diff check */
	arx_diff_search_two();
	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
	arx_diff_search_three();
//	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
//	arx_diff_search_four();
//	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
//	arx_diff_search_five();
	/* Best rot search */
//	arx_best_rot_two();
//	arx_best_rot_three();
//	arx_best_rot_four();
//	arx_best_rot_five();
//	arx_best_rot_six();

	printf("Calculation done in %0.1f seconds...\n", (double)(clock() - c) / CLOCKS_PER_SEC);
	return 0;
}
