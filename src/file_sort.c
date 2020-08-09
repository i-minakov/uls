#include "../inc/uls.h"

void file_sort(t_list **list) {
    t_list *t = *list;
    int f_count = 0;
    for (t_list *i = t->next; i->next; i = i->next, f_count++) {
        char *min = i->data;
        int sec_count = f_count + 1;
        int res_count;
        for (t_list *j = i->next; j; j = j->next, sec_count++) { // kogda == ?
            if (mx_strcmp(j->data, min) < 0) {
                min = j->data;
                res_count = sec_count;
            }
        }
        if (mx_strcmp(min, i->data) != 0) {
            t_list *swap = t->next;
            for( int k = 0; k < res_count; k++, swap = swap->next);
            char *tmp = i->data;
            i->data = swap->data;
            swap->data = tmp;
            min = i->data;
        }
    }
}
