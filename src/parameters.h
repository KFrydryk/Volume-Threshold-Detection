#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <stdint.h>
#include <stddef.h>

/* time in ms */
#define AVERAGING_TIME 500

/* threshold levels relative to full scale*/
static uint32_t thresholds[] = {
	INT32_MAX/256,
	INT32_MAX/128,
	INT32_MAX/64,
	INT32_MAX/32,
	INT32_MAX/16,
	INT32_MAX/8,
	INT32_MAX/4,
	INT32_MAX/2
};

static const size_t thresholds_num = sizeof(thresholds)/sizeof(uint32_t);

#endif
