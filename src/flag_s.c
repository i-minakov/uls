#include "../inc/uls.h"

static int mx_max(long long kek[], int len) {
    int res = 0;
    for (int i = 0; i < len; i++) {
        char *tmp = mx_itoa(kek[i]);
        if (res < mx_strlen(tmp))
            res = mx_strlen(tmp);
        free(tmp);
    }
    return res;
}

static char *pivo(int l, char *tmp) {
    char *res = NULL;
    while (mx_strlen(tmp) < l) {
        res = mx_delit_fre(res, " ");
        l--;
    }
    return res;
}

static void for_s(long long kek[], t_list *list) {
    for (int i = 0; i < (mx_list_size(list) - 1); i++)
        kek[i] = 0;
    int i = 0;
    char *name = list->data;
    for (t_list *t = list->next; t; t = t->next, i++) {
        struct stat inf;
        char *p = mx_abs_filename(name, t->data);
        lstat(p, &inf);
        kek[i] = inf.st_blocks;
        free(p);
    }
}

static char *mx_hate(char *name, char *dir_name) {
    char *p = NULL;
    p = mx_abs_filename(dir_name, name);
    return p;
}

char *flag_s(char *name, t_list *list) {
    char *res = NULL;
    struct stat inf;
    long long kek[mx_list_size(list) - 1];
    for (int i = 0; i < (mx_list_size(list) - 1); i++)
        kek[i] = 0;
    for_s(kek, list);
    char *p = mx_hate(name, list->data);
    lstat(p, &inf);
    free(p);
    int l = mx_max(kek, (mx_list_size(list) - 1));
    char *tmp = mx_itoa(inf.st_blocks);
    res = mx_cooljoin(res, pivo(l, tmp));
    res = mx_cooljoin(res, tmp);
    res = mx_delit_fre(res, " ");
    return res;
}


