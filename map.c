#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "error.h"
#include "utils.h"
#include "list.h"
#include "scripting.h"
#include "map.h"

mrc_List *mapResults;

void mrc_map_init() {
	mapResults = mrc_new_list();
}

void mrc_map_apply(char *line) {
    mrc_scripting_map(line);
}

void mrc_map_callback(const char *key, const char *value) {
	mrc_MapEntry *entry = malloc(sizeof(mrc_MapEntry));
    entry->key = (void*)mrc_alloc_string(key);
    entry->value = (void*)mrc_alloc_string(value);
    mrc_list_append(mapResults, entry);
}

void mrc_map_writeout(const char *outputLocation) {
    FILE *output = fopen(outputLocation, "w");

    void *tEntry = NULL;
    while (mrc_list_pop(mapResults, &tEntry)) {
        mrc_MapEntry *entry = (mrc_MapEntry*)tEntry;
        fprintf(output, "%s%s%s\n", entry->key, MR_MAP_KEYVAL_SEPARATOR, entry->value);
    }

    fclose(output);
    mrc_list_delete(mapResults);
}

void mrc_map_sort() {
    // todo use a sort besides bubble sort. doing this for quick implementation.
    if (mapResults == NULL || mrc_list_length(mapResults) == 0) {
        mrc_error("No map results");
    } else {
        int changed = 0;
        do {
            changed = 0;

            mrc_Node *current = mapResults->head;
            while (current != NULL) {
                if (current->next != NULL && strcmp(((mrc_MapEntry*)current->data)->key, ((mrc_MapEntry*)current->next->data)->key) > 0) {
                    changed = 1;

                    void *currentData = current->data;
                    current->data = current->next->data;
                    current->next->data = currentData;
                }
                current = current->next;
            }
        } while (changed);
    }
}