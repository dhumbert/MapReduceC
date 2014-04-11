#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "list.h"
#include "mrc.h"

/* lua interpreter */
lua_State* l;
FILE *input;
List *mapResults;

int main (int argc, char* argv[]) {
    // todo getopt_long

    /* initialize lua */
    l = lua_open();

    /* load lua libraries */
    luaL_openlibs(l);

    /* run the hello.lua script */
    int dofile = luaL_dofile(l, "map.lua");

    if (dofile == 0) {
        mapResults = new_list();
        input = fopen("samples/masque.txt", "r");
        if (input == NULL) {
            error("Unable to open file samples/masque.txt");
        } else {
            char *line;
            size_t len = 0;
            ssize_t read;

            while ((read = getline(&line, &len, input)) != -1) {
                trim(line);
                if (read > 1 || strlen(line) > 0) { // todo trim whitespace
                    map_map(line);
                }
            }
            fclose(input);

            map_sort();
            map_writeout("map_output.tmp");

            free(line);
        }
        
    } else {
        printf("Error, unable to run map.lua\n");
    }

    /* cleanup Lua */
    lua_close(l);

    return 0;
}

void map_map(char *line) {
    lua_getglobal(l,"map");
    lua_pushstring(l, line);
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
                MapEntry *entry = malloc(sizeof(MapEntry));
                entry->key = (void*)key;
                entry->value = (void*)value;
                list_append(mapResults, entry);
            }
        } else {
            error("Map key and map value must both be strings.");
        }
    }
}

void map_writeout(const char *outputLocation) {
    FILE *output = fopen(outputLocation, "w");

    void *tEntry = NULL;
    while (list_pop(mapResults, &tEntry)) {
        MapEntry *entry = (MapEntry*)tEntry;
        fprintf(output, "%s%s%s\n", entry->key, MR_MAP_KEYVAL_SEPARATOR, entry->value);
    }

    fclose(output);
    list_delete(mapResults);
}

void map_sort() {
    // todo use a sort besides bubble sort. doing this for quick implementation.
    if (mapResults == NULL || list_length(mapResults) == 0) {
        error("No map results");
    } else {
        int changed = 0;
        do {
            changed = 0;

            Node *current = mapResults->head;
            while (current != NULL) {
                if (current->next != NULL && strcmp(((MapEntry*)current->data)->key, ((MapEntry*)current->next->data)->key) > 0) {
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

static void debug_print_list(List *list, int limit) {
    Node *current = list->head;
    while (current != NULL && limit > 0) {
        printf("%s\n", ((MapEntry*)current->data)->key);
        current = current->next;
        limit--;
    }
}

void error(const char *msg) {
    printf("ERROR: %s\n", msg);
    exit(1);
}

char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str - 1;
    char *endp = NULL;

    if( str == NULL )
            return NULL;

    if( str[0] == '\0' )
            return str;

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address
     * the first non-whitespace characters from
     * each end.
     */
    while( isspace(*(++frontp)) );
    while( isspace(*(--endp)) && endp != frontp );

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so
     * that if it's dynamically allocated, we can
     * still free it on the returned pointer.  Note
     * the reuse of endp to mean the front of the
     * string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) *endp++ = *frontp++;
            *endp = '\0';
    }


    return str;
}


//printf("%s\n", lua_typename(l, lua_type(l, -1)));
