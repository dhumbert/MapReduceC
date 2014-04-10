#include <stdlib.h>
#include "list.h"

/**
 * Allocate and initialize a new list.
 */
List *new_list() {
	List *list = malloc(sizeof(List));
	list->head = NULL;
	list->last = NULL;
	list->length = 0;
	return list;
}

/**
 * Push a value onto the front of a list.
 */
void list_push(List *list, void *data) {
	Node *node = malloc(sizeof(Node));
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
void list_append(List *list, void *data) {
	Node *node = malloc(sizeof(Node));
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
int list_length(List *list) {
	return list->length;
}

/**
 * Access list elements by index, like an array.
 */
void *list_get(List* list, int idx) {
	if (list == NULL || list_length(list) == 0) {
		return NULL;
	} else {
		int i = 0;
		Node *current = list->head;
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
int list_pop(List *list, void **data) {
	if (list->head == NULL) {
		return 0;
	} else {
		*data = list->head->data;
		list_remove(list, list->head);
		return 1;
	}
}

/**
 * Remove a node from a list.
 */
void list_remove(List *list, Node *node) {
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
		Node *after = node->next;
		Node *before = node->prev;
		after->prev = before;
		before->next = after;
	}

	free(node);
	list->length--;
}

void list_delete(List *list) {
	if (list == NULL) {
		return;
	}

	if (list_length(list) > 0) {
		Node *current, *next;
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