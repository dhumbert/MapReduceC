#include <stdlib.h>
#include "lualib.h"
#include "lauxlib.h"
#include "error.h"
#include "types.h"
#include "utils.h"
#include "list.h"
#include "scripting.h"

/* lua interpreter */
lua_State* l;
mrc_Callback map_callback;

static int mrc_scripting_lua_emit(lua_State *l) {
    int n = lua_gettop(l); // number of args
    if (n != 2) {
        mrc_error("Incorrect number of arguments to emit");
    }

    if (lua_isstring(l, -1) && lua_isstring(l, -2)) {
        size_t keylen, vallen;
        const char *key = lua_tolstring(l, -2, &keylen);
        const char *value = lua_tolstring(l, -1, &vallen);

        if (keylen < 1) { // todo trim surrounding whitespace first
            mrc_error("Map key must not be blank");
        } else {
            map_callback(key, value);
        }
    } else {
        mrc_error("Map key and map value must both be strings.");
    }

    return 0;
}

int mrc_scripting_init(const char *filename, mrc_Callback mcb) {
	map_callback = mcb;

	/* initialize lua */
    l = lua_open();

    /* load lua libraries */
    luaL_openlibs(l);

    /* run the hello.lua script */
    int dofile = luaL_dofile(l, filename);

    lua_pushcfunction(l, mrc_scripting_lua_emit);
    lua_setglobal(l, "emit");

    return dofile;
}

void mrc_scripting_map(char *line) {
    lua_getglobal(l,"map");
    lua_pushstring(l, line);
    if (lua_pcall(l,1,1,0) != 0) {
        mrc_error(lua_tostring(l, -1));
    }
}

void mrc_scripting_close() {
	/* cleanup Lua */
    lua_close(l);
}