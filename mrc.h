#ifndef _MRC_H
#define _MRC_H

#define MR_MAP_KEYVAL_SEPARATOR "\t"

typedef struct MapEntry {
	void *key;
	void *value;
} MapEntry;

void map_map(char*);
void map_sort(void);
void map_writeout(const char*);
void error(const char*);
char *trim(char*);
static void debug_print_list(List*, int);
#endif