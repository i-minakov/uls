#include "../inc/uls.h"

static void mx_flags(t_list **all, t_flag *c) {
    if (c->s != 1 && c->i != 1) 
        return ;
    t_list *a = *all;
    char *m = NULL; 
    for (t_list *t = a->next; t; t = t->next) {
        c->i == 1 ? m = mx_cooljoin(m, flag_i(t->data, a)) : 0;
        c->s == 1 ? m = mx_cooljoin(m, flag_s(t->data, a)) : 0;
        m = mx_delit_fre(m, "*");
    }
    char **o = mx_strsplit(m, '*');
    int j = 0;
    for (t_list *t = a->next; t; t = t->next) {
        t->data = mx_cooljoin(o[j], t->data);
        j++;
    }
    // mx_del_strarr(&o);
    free(o);
    free(m);
}

static void for_struct(t_flag *variable, char *flags) {
    if (mx_get_char_index(flags, 's') >= 0)
        variable->s = 1;
    else 
        variable->total = -1;
    if (mx_get_char_index(flags, 'i') >= 0)
        variable->i = 1;
    if (mx_get_char_index(flags, '1') >= 0)
        variable->one = 1;
     if (mx_get_char_index(flags, 'C') >= 0)
        variable->C = 1;
    if (mx_get_char_index(flags, '@') >= 0)
        variable->ext = 1;
    if (mx_get_char_index(flags, 'u') >= 0)
        variable->u = 1;
}

int flag_check(t_list **all, char *flags, t_flag *variable) {
    int res = 0;
    if (flags[0] != '-') 
        return -1;
    for_struct(variable, flags);
    sort_check(all, flags);
    if (mx_get_char_index(flags, 'l') >= 0) {
        res = 1;
        if (mx_get_char_index(flags, 'e') >= 0)
            variable->e = 1;
        if(variable->one != 1 || (mx_get_char_index(flags, 'l') - 
            mx_get_char_index(flags, '1') > 0))
            ls_l(*all, variable);
    }
    variable->total = mx_total(*all);
    if (res == 0) 
        mx_flags(all, variable);
    return res;
}
