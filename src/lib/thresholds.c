#include "include/thresholds.h"
#include <errno.h>
#include <stddef.h>

int threshold_next(struct threshold *thr)
{
	if (thr->lli == NULL)
		return -EINVAL;

	thr->lli = thr->lli->next;
	thr->val = *(uint32_t *)thr->lli->data;

	return 0;
}

int threshold_init(struct threshold *thr, struct linked_list *lli)
{
	if ((thr == NULL) || (lli == NULL))
		return -EINVAL;

	thr->lli = lli;
	thr->val = *(uint32_t *)lli->data;

	return 0;
}
