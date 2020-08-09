#include "../inc/uls.h"

void free_list_arr(t_list ***l) {
    t_list **list = *l;
    for( int i = 0; list[i]; i++)
        free_list(&list[i]);
    free(list);
}


