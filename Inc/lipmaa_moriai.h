#ifndef LIPMAA_MORIAI_H_
#define LIPMAA_MORIAI_H_

#include "config.h"
#include "utils.h"

void lipmaa_moriai();
void lipmaa_moriai_check(const uint32_t xdp[256][256], const uint32_t space);

void lipmaa_moriai_3();
void lipmaa_moriai_check_3(const double *xdp, const uint32_t space);

double XDP_TOTAL[256 * 256 * 256];

#endif /* LIPMAA_MORIAI_H_ */
