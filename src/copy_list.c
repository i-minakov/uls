#include "../inc/uls.h"

t_list *copy_list(t_list *l) {
    t_list *res = NULL;
    for (; l; l = l->next)
        mx_push_back(&res, mx_strdup(l->data));
    return res;
}
