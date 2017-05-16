#ifndef ANALYZER_H_
#define ANALYZER_H_

#include "utils.h"
#include "config.h"
#include "ciphers.h"

/* Diff analysis */
/* s-box */
void arx_diff_search_sbox_two();
void arx_diff_search_sbox_three();
/* ARX-GOST */
void arx_diff_search_two();
void arx_diff_search_three();
void arx_diff_search_four();
void arx_diff_search_five();

/* Rotational analysis */
void arx_rotation_search_two();
void arx_rotation_search_three();
void arx_rotation_search_four();
void arx_rotation_search_five();
void arx_rotation_search_six();
void arx_rotation_search_three_recount();

/* Best rot search */
void arx_best_rot_two();
void arx_best_rot_three();
void arx_best_rot_four();
void arx_best_rot_five();
void arx_best_rot_six();

#if (BLOCK_BIT_LEN == 8)
#define XDP XDP_8
#elif (BLOCK_BIT_LEN == 16)
#define XDP XDP_16
#endif

#endif /* ANALYZER_H_ */
