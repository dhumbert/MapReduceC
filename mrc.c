#include <stdio.h>
#include <stdlib.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "mrc.h"

/* lua interpreter */
lua_State* l;

int main () {
    /* initialize lua */
    l = lua_open();

    /* load lua libraries */
    luaL_openlibs(l);

    /* run the hello.lua script */
    int dofile = luaL_dofile(l, "map.lua");

    if (dofile == 0) {
        do_map();
    } else {
        printf("Error, unable to run map.lua\n");
    }

    /* cleanup Lua */
    lua_close(l);

    return 0;
}

void do_map() {
    lua_getglobal(l,"map");
    lua_pushstring(l, "Devin");
    if (lua_pcall(l,1,1,0) != 0) {
        error(lua_tostring(l, -1));
    } else {
        lua_rawgeti(l, -1, 2); // value
        lua_rawgeti(l, -2, 1); // key
        if (lua_isstring(l, -1) && lua_isstring(l, -2)) {
            size_t keylen, vallen;
            const char *key = lua_tolstring(l, -1, &keylen);
            const char *value = lua_tolstring(l, -2, &vallen);

            if (keylen < 1) { // todo trim surrounding whitespace first
                error("Map key must not be blank");
            } else {
                printf("Key: %s, Value: %s\n", key, value);
            }
        } else {
            error("Map key and map value must both be strings.");
        }
    }
}

void error(const char *msg) {
    printf("ERROR: %s\n", msg);
    exit(1);
}


//printf("%s\n", lua_typename(l, lua_type(l, -1)));
