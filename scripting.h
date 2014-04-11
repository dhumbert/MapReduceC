#ifndef _SCRIPTING_H
#define _SCRIPTING_H
#include "lua.h"
#include "types.h"

int mrc_scripting_init(const char*, mrc_Callback);
void mrc_scripting_close(void);
void mrc_scripting_map(char*);

#endif