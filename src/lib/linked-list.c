#include <stddef.h>
#include <errno.h>
#include "include/linked-list.h"

int linked_list_init(struct linked_list *list)
{
	if (list == NULL)
		return -EINVAL;
	list->prev = list;
	list->next = list;

	return 0;
}

int linked_list_append(struct linked_list *target, struct linked_list *item)
{
	struct linked_list *temp;

	/* check if both list exist */
	if ((target == NULL) || (item == NULL))
		return -EINVAL;

	/* sanity check. Uninitialized pointers are not null, so how does this even happen? */
	if ((target->prev == NULL) || (target->next == NULL))
		return -EINVAL;

	/* store target next value */
	temp = target->next;
	/* place new item after target */
	target->next = item;
	/* fill in items links */
	item->prev = target;
	item->next = temp;
	/* assign next value new "prev" val */
	temp->prev = item;

	return 0;
}
