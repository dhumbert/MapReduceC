#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "list.h"
#include "error.h"
#include "scripting.h"
#include "map.h"
#include "utils.h"
#include "types.h"
#include "mrc.h"

FILE *input;

int main (int argc, char* argv[]) {
    // todo getopt_long

    int scripting = mrc_scripting_init("map.lua", &mrc_map_callback);

    if (scripting == 0) {
        
        input = fopen("samples/masque.txt", "r");
        if (input == NULL) {
            mrc_error("Unable to open file samples/masque.txt");
        } else {
            char *line;
            size_t len = 0;
            ssize_t read;

            mrc_map_init();

            while ((read = getline(&line, &len, input)) != -1) {
                mrc_trim(line);
                if (read > 1 || strlen(line) > 0) { // todo trim whitespace
                    mrc_map_apply(line);
                }
            }
            fclose(input);

            mrc_map_sort();
            mrc_map_writeout("map_output.tmp");

            free(line);
        }
        
    } else {
        mrc_error("Error, unable to run map.");
    }

    mrc_scripting_close();

    return 0;
}

// static void debug_print_list(mrc_List *list, int limit) {
//     mrc_Node *current = list->head;
//     while (current != NULL && limit > 0) {
//         printf("%s\n", ((mrc_MapEntry*)current->data)->key);
//         current = current->next;
//         limit--;
//     }
// }






//printf("%s\n", lua_typename(l, lua_type(l, -1)));
