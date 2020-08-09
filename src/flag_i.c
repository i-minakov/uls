#include "../inc/uls.h"

static void for_i(char **kek, t_list *list) {
    int i = 0;
    char *name = list->data;
    for (t_list *t = list->next; t; t = t->next, i++) {
        struct stat inf;
        char *p = mx_abs_filename(name, t->data);
        lstat(p, &inf);
        kek[i] = mx_itoa(inf.st_ino);
        free(p);
    }
}

static char *pivo(int l, char *tmp) {
    char *res = NULL;
    while (mx_strlen(tmp) < l) {
        res = mx_delit_fre(res, " ");
        l--;
    }
    return res;
}

static int mx_max(char **kek, int len) {
    int res = 0;
    for (int i = 0; i < len; i++) {
        char *tmp = kek[i];
        if (res < mx_strlen(tmp))
            res = mx_strlen(tmp);
    }
    return res;
}

static char *mx_hate(char *name, char *dir_name) {
    char *p = NULL;
    p = mx_abs_filename(dir_name, name);
    return p;
}


char *flag_i(char *name, t_list *list) {
    char *res = NULL;
    struct stat inf;
    char **kek = (char **)malloc(sizeof(char *) * (mx_list_size(list)));
    kek[mx_list_size(list) - 1] = NULL;
    for_i(kek, list);
    char *p = mx_hate(name, list->data);
    lstat(p, &inf);
    free(p);
    int l = mx_max(kek, (mx_list_size(list) - 1));
    char *tmp = mx_itoa(inf.st_ino);
    res = mx_cooljoin(res, pivo(l, tmp));
    res = mx_cooljoin(res, tmp);
    res = mx_delit_fre(res, " ");
    mx_del_strarr(&kek);
    return res;
}

