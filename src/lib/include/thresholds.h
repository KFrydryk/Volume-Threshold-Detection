#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "linked-list.h"
#include <stdint.h>
#include <stdbool.h>

struct threshold {
	struct linked_list *lli;
	uint32_t val;
};

int threshold_next(struct threshold *thr);
int threshold_init(struct threshold *thr, struct linked_list *lli);

#endif
