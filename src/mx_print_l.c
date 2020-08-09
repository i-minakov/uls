#include "../inc/uls.h"

static void mx_print_else(char **buf, char *dir) {
    write(1, buf[5], mx_strlen(buf[5]));
    write(1, " ", 1);
    char *p = mx_abs_filename(dir, buf[6]);
    char *q = mx_link(buf[6], p, buf[0]);
    char *c = check(q);
    mx_printstr(c);
    free(c);
    free(p);
    free(q);
    if (buf[7]) 
        mx_printstr(buf[7]);
}

 
static void mx_print_total(t_list *list) {
    write(1, "total ", mx_strlen("total "));
    mx_printint(mx_total(list));
    write(1, "\n", 1);
}


static void mx_print_col(char *buf, t_print *p, int k) {
    int l = p->max_len[k - 1];

    if (k == 2 || k == 3)
        mx_printstr(buf);
    for (; mx_strlen(buf) < l; l--)
        write(1, " ", 1);
    if (k == 1 || k == 4)
        mx_printstr(buf);
    if (k == 2 || k == 3) 
        write(1, " ", 1);
    write(1, " ", 1);
}


void mx_print_l(char **res, t_list *list, t_print *p) {
    if (p->flags->R == 2 && mx_strcmp(list->data, ".") != 0) {
        mx_printstr(list->data);
        write(1, ":\n", 2);
    }
    if (mx_total(list) != -1)
        mx_print_total(list);
    mx_print_utils(res, p);
    for (int i = 0; i < p->list_size; i++) {
        char **buf = mx_strsplit(res[i], '*');
        if (p->flags->i == 1) 
            mx_super_printstr(flag_i(buf[6], list));
        if (p->flags->s == 1)
            mx_super_printstr(flag_s(buf[6], list));
        mx_printstr(buf[0]);
        write(1, " ", 1);
        for (int k = 1; k != 5; k++)
            mx_print_col(buf[k], p, k);
        mx_print_else(buf, list->data);
        mx_del_strarr(&buf);
        write(1, "\n", 1);
    }
}
