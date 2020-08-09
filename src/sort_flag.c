#include "../inc/uls.h"

static void sort_at(t_list **list, bool (*cmp)(char *, char *) ) {
    t_list *t = *list;
    int f = 0;
    while (!f) {
        f = 1;
        for (t_list *r = t->next; r->next; r = r->next) {
            if (cmp(mx_abs_filename(t->data, r->data), 
                    mx_abs_filename(t->data, r->next->data))) {
                char *tmp = r->data;
                r->data = r->next->data;
                r->next->data = tmp;
                f = 0;
            }
        }
    }
}

void sort_check(t_list **list, char *flags) {
    t_list *t = *list;
    if (t->next == NULL)
        return;
    if (mx_get_char_index(flags, 'S') >= 0) {
        sort_at(list, cmp_blocks);
    }
    else {
        if (mx_get_char_index(flags, 't') >= 0) {
            if (mx_get_char_index(flags, 'u') >= 0)
                sort_at(list, cmp_utime);
            else 
                sort_at(list, cmp_time);
        }
    }
    if (mx_get_char_index(flags, 'r') >= 0) {
        r_sort(list);
    }
}
