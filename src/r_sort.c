#include "../inc/uls.h"

void r_sort(t_list **list) {
    t_list *t = *list;
    t = t->next;
    int count = 0;
    int chan = 0;
    for (t_list *tmp = t; tmp->next; tmp = tmp->next)
        count++;
    int sr = count/2;
    while (chan <= sr) {
        t_list *c = t;
        for (int i = 0; i < count; i++)
            c = c->next;
            char *tmp = c->data;
            c->data = t->data;
            t->data = tmp;
            t = t->next;
            count -= 2;
            chan++;
    }
}


