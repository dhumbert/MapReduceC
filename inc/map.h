#ifndef _MAP_H
#define _MAP_H
#define MR_MAP_KEYVAL_SEPARATOR "\t"

void mrc_map_init(void);
void mrc_map_apply(char*);
void mrc_map_writeout(const char*);
void mrc_map_sort();
void mrc_map_callback(const char*, const char*);

#endif