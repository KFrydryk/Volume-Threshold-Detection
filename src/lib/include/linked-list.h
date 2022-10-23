#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct linked_list {
	struct linked_list *prev;
	struct linked_list *next;
	void *data;
};

int linked_list_init(struct linked_list *list);
int linked_list_append(struct linked_list *target, struct linked_list *item);

#endif
