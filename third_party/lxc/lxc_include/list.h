#ifndef _list_h
#define _list_h

struct lxc_list {
	void *elem;
	struct lxc_list *next;
	struct lxc_list *prev;

#define lxc_init_list(l) { .next = l, .prev = l }
