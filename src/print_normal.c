#include "../inc/uls.h"

static void f_or_err(t_list *st, char *name, t_flag *c) {
    if (!errcheck(name)) {
        int i = 0;
        char **buf = mx_strsplit(name, '/');
        for( ; buf[i]; i++);
        if (c->flag == 2) {
            write(1, st->data, mx_strlen(st->data));
            write(1, ":\n", 2);
        }
        globalcheck(name, buf[i - 1]);
        mx_del_strarr(&buf);
    }
    else {
        write(1, st->data, mx_strlen(st->data));
        write(1, "\n", 1);
    }
}

static void print_folder(t_flag *c, char *name, t_list *st) {
    if (c->flag == 2) {
            write(1, name, mx_strlen(name));
            write(1, ":\n", 2);
        }
    if(c->total != -1 && c->s == 1) {
        write(1, "total ", mx_strlen("total "));
        mx_printint(c->total);
        write(1, "\n", 1);
    }
    if (mx_strcmp(st->data, name) == 0) 
        return;
    for (t_list *tmp = st; tmp; tmp = tmp->next) {
        write(1, tmp->data, mx_strlen(tmp->data));
        write(1, "\n", 1);
    }
}

void print_normal(t_list *st, char *name, t_flag *c) {
    if(name == NULL) {
        for (t_list *tmp = st; tmp; tmp = tmp->next) {
            write(1, tmp->data, mx_strlen(tmp->data));
            write(1, "\n", 1);
        }
        return;
    }
    if (!opencheck(name, 1) && st->next == NULL) //vrode 1 no mozet 2
        f_or_err(st, name, c);
    else
        print_folder( c, name, st);  
}
