#ifndef GP_TIMER_H
#define GP_TIMER_H

#include "stdint.h"
#include <stdbool.h>

struct gp_timer {
	int instance;
	bool enable;
	uint16_t prescaler;
	uint32_t threshold;
};

int gp_timer_init(struct gp_timer *tmr, int inst);
/* configure runs set_prescaler and set_threshold itnernally */
int gp_timer_configure(struct gp_timer *tmr, uint16_t presc, uint32_t thr);
int gp_timer_set_prescaler(struct gp_timer *tmr);
int gp_timer_set_threshold(struct gp_timer *tmr);
int gp_timer_start(struct gp_timer *tmr);
int gp_timer_stop(struct gp_timer *tmr);

#endif
