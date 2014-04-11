#include <stdlib.h>
#include "list.h"

/**
 * Allocate and initialize a new list.
 */
mrc_List *mrc_new_list() {
	mrc_List *list = malloc(sizeof(mrc_List));
	list->head = NULL;
	list->last = NULL;
	list->length = 0;
	return list;
}

/**
 * Push a value onto the front of a list.
 */
void mrc_list_push(mrc_List *list, void *data) {
	mrc_Node *node = malloc(sizeof(mrc_Node));
	node->data = data;
	node->prev = NULL;
	node->next = list->head;
	
	if (list->head != NULL) {
		list->head->prev = node;
	}

	if (list->last == NULL) {
		list->last = node;
	}

	list->head = node;
	list->length++;
}

/**
 * Append a value to the back of a list.
 */
void mrc_list_append(mrc_List *list, void *data) {
	mrc_Node *node = malloc(sizeof(mrc_Node));
	node->data = data;
	node->prev = list->last;

	if (list->head == NULL) {
		list->head = node;
	}

	if (list->last != NULL) {
		list->last->next = node;
	}

	node->next = NULL;
	list->last = node;
	list->length++;
}

/**
 * Get the length of a list.
 */
int mrc_list_length(mrc_List *list) {
	return list->length;
}

/**
 * Access list elements by index, like an array.
 */
void *mrc_list_get(mrc_List* list, int idx) {
	if (list == NULL || mrc_list_length(list) == 0) {
		return NULL;
	} else {
		int i = 0;
		mrc_Node *current = list->head;
		while (current != NULL) {
			if (i == idx) {
				return current->data;
			}

			current = current->next;
			i++;
		}
	}

	return NULL;
}

/**
 * Pop a value off the front of a list.
 */ 
int mrc_list_pop(mrc_List *list, void **data) {
	if (list->head == NULL) {
		return 0;
	} else {
		*data = list->head->data;
		mrc_list_remove(list, list->head);
		return 1;
	}
}

/**
 * Remove a node from a list.
 */
void mrc_list_remove(mrc_List *list, mrc_Node *node) {
	if (node == list->head && node == list->last) {
		list->head = NULL;
		list->last = NULL;
	} else if (node == list->head) {
		list->head = node->next;
		list->head->prev = NULL;
	} else if (node == list->last) {
		list->last = node->prev;
		list->last->next = NULL;
	} else {
		mrc_Node *after = node->next;
		mrc_Node *before = node->prev;
		after->prev = before;
		before->next = after;
	}

	free(node);
	list->length--;
}

void mrc_list_delete(mrc_List *list) {
	if (list == NULL) {
		return;
	}

	if (mrc_list_length(list) > 0) {
		mrc_Node *current, *next;
		current = list->head;
		while (current != NULL) {
			next = current->next;

			if (current->data != NULL) {
				free(current->data);
				current->data = NULL;
			}

			free(current);
			list->length--;
			current = next;
		}
	}
}