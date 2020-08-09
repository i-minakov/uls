#include "../inc/uls.h"

static void do_do_do(t_list **res, t_flag *variable, char *flags, int j) {
    int flagforl = 0;
    if (flags[0] == '-' && mx_get_char_index(flags, 'R') > 0) {
        variable->R = 2;
        its_R(res[j], flags, variable);
    }
    else {
        flagforl = flag_check(&res[j], flags, variable);
        its_not_R(flagforl, res[j], variable, flags);
    }
    if (res[j + 1]) 
        write(1, "\n", 1);
}

static void do_do(t_list **res, t_flag *variable, char *flags) {
    for (int j = 0; res[j]; j++) {
        char *p = mx_abs_filename(NULL, res[j]->data);
        if (!errcheck(p)) {
            if (variable->R == 2) {
                write(2, res[j]->data, mx_strlen(res[j]->data));
                write(2, ":\n", 2);
            }
            perm_den(res[j]->data, res[j]->data);
            if (res[j + 1])
                write(1, "\n", 1);
        }
        else
            do_do_do( res, variable, flags, j);
        free(p);
    }
}

static void ya_lublu_anime(char *c, t_flag *variable) {
    t_list *res = crate_ls(c, ".");
    int flagforl = 0;
    variable->total = mx_total(res);
        if (c[0] == '-' && mx_get_char_index(c, 'R') > 0) {
            variable->R = 2;
            its_R(res, c, variable);
        }
        else {
            flagforl = flag_check(&res, c, variable);
            its_not_R(flagforl, res, variable, c);
        }
    exit(0);
}

static void ya_lublu_kogda_mnogo_anime(int arg, char *c[], char *flags, t_flag *variable) {
    int i = start_words(c) + 1;
    int dt = data_check(arg, c, variable, i);
    int o = i;
    t_list **res = (t_list **)malloc(sizeof(t_list *) * (dt + 1));
    res[dt] = NULL; 
    for (int j = 0; c[i]; i++)
        if (opencheck(c[i], variable->l)) {
            res[j] = crate_ls(flags, c[i]);
            j++;
        }
    sort_list(&res, flags);
    if (c[o + 1] != NULL) {
        variable->flag = 2;
        variable->R = 2;
    }
    do_do( res, variable, flags);
    free_list_arr(&res);
}

int main(int arg, char *c[]) {
    t_flag *variable = (t_flag *)malloc(sizeof(t_flag) * 11);
    variable->flag = 1;
    char *flags = start_flags(c);
    if (mx_get_char_index(flags, 'l') > mx_get_char_index(flags, '1'))
        variable->l = 2;
    else 
        variable->l = 1;
    bad_flag(flags);
    int amo = start_words(c) + 1;
    if (arg == 1 || ((arg - amo) == 0 && c[1][0] == '-'))
        ya_lublu_anime(flags, variable); // kogda .
    ya_lublu_kogda_mnogo_anime(arg, c, flags, variable); // lubaya drugaya papka
    free(flags);
    flags = NULL;
    free(variable);
    // write(1, "\n", 1);
    // system("leaks -q uls");
    return 0;
}




