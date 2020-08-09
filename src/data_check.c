#include "../inc/uls.h"


static void mx_check(t_list *f, char *c[], int res, t_flag *variable) {
    if (f->next) {
        if (f->next->next)
            file_sort(&f);
        int flag = flag_check(&f, c[1], variable);
        t_list *s = stolb(f);
        if (flag != 1)
            print_normal(s, NULL, 0);
        free_list(&f);
        free_list(&s);
        if (res == 0) 
            exit(0);
        write(1, "\n", 1);
    }
    else 
        free(f);
}

static void mx_busya(char *n) {
    if (n == NULL) 
        return ;
    char **m = mx_strsplit(n, '*');
    buble_s(m);
    for (int i = 0; m[i]; i++)
        no_file(m[i], 2);
    mx_del_strarr(&m);
    free(n);
}

static bool dev_fd(char *dirname) {
    if (mx_get_substr_index(dirname, "dev/fd/3") > -1) {
        write(1, "uls: /dev/fd/3: Bad file descriptor", 35);
        return true;
    }
    return false;
}


int data_check(int arg, char *c[], t_flag *variable, int start) {
    int res = 0;
    t_list *f = mx_create_node(NULL);
    char *nofile = NULL;
    for (int i = start; i < arg; i++) {
        if (dev_fd(c[i]))
            continue ;
        else {
            if (no_file(c[i], 1)) {
                if (!opencheck(c[i], variable->l)) 
                    mx_push_back(&f, mx_strdup(c[i]));
                else 
                    res++;
            }
            else {
                nofile = mx_delit_fre(nofile, c[i]);
                nofile = mx_delit_fre(nofile, "*");
            }
        }
    }
    mx_busya(nofile);
    mx_check(f, c, res, variable);
    return res;
}
