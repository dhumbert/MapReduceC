#ifndef _LIST_H

/**
 * Nodes for a doubly-linked list.
 */
typedef struct mrc_Node {
	void *data;
	struct mrc_Node *prev;
	struct mrc_Node *next;
} mrc_Node;

/**
 * Data type to abstract a list.
 */
typedef struct mrc_List {
	mrc_Node *head;
	mrc_Node *last;
	int length;
} mrc_List;


mrc_List *mrc_new_list();
void mrc_list_push(mrc_List*, void*);
void mrc_list_append(mrc_List*, void*);
int mrc_list_length(mrc_List*);
void *mrc_list_get(mrc_List*, int);
int mrc_list_pop(mrc_List*, void**);
void mrc_list_remove(mrc_List*, mrc_Node*);
void mrc_list_print(mrc_List*);
void mrc_list_delete(mrc_List*);
#define _LIST_H
#endif