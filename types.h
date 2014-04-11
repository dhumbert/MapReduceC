#ifndef _TYPES_H
#define _TYPES_H
#define SUPPRESS_WARNING(a) (void)a

typedef struct mrc_MapEntry {
	void *key;
	void *value;
} mrc_MapEntry;

typedef void (*mrc_Callback)(const char*, const char*);

#endif