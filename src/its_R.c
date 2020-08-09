#include "../inc/uls.h"

void its_R(t_list *res, char *c, t_flag *variable) {
    char *n = NULL;
    n = mx_strjoin(n, res->data);
    a_eto_R(n, c, variable);
}

