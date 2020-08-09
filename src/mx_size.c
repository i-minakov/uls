#include "../inc/uls.h"

static char *lenn_of_the_null(char *src) {
    int lenn = mx_strlen(src);
    char *s = NULL;

    s = mx_strjoin(s, "0x");
    for (int i = 0; i < 8 - lenn; i++)
        s = mx_delit_fre(s, "0");
    s = mx_delit_fre(s, src);
    free(src);
    return s;
}

char *mx_min(struct stat stbuf) {
    char *s = NULL;
    int min = MX_MAJOR(stbuf.st_rdev);

    if (min > 256)
        s = lenn_of_the_null(mx_nbr_to_hex(min));
    else
        s = mx_itoa(min);
    return s;
}

char *mx_maj(struct stat stbuf) {
    char *s = NULL;
    int maj = MX_MINOR(stbuf.st_rdev);

    if (maj > 256)
        s = lenn_of_the_null(mx_nbr_to_hex(maj));
    else
        s = mx_itoa(maj);
    return s;
}

char *mx_max(struct stat inf, char **m, int f) {
    char *res = NULL;
    int max = 0;
    for (int i = 0; m[i]; i++){
        if (mx_strlen(m[i]) > max && mx_strlen(m[i]) < 9)
            max = mx_strlen(m[i]);
    }
    char *tmp = NULL;
    if (f == 1) 
        tmp = mx_min(inf);
    if (f == 2)
        tmp = mx_maj(inf);
    for (; mx_strlen(tmp) < max; max--)
        res = mx_delit_fre(res, " ");
    res = mx_cooljoin(res, tmp);
    return res;
}

char *mx_size(struct stat inf, char str[], t_list *a) {
    char *res = NULL;
	if (str[0] == 'c' || str[0] == 'b') {
        for (int i = 1; i <= 2; i++) {
            char **m = (char **)malloc(sizeof(char*)*(mx_list_size(a)));
            m[mx_list_size(a) - 1] = NULL;
            int h = 0;
            for (t_list *tmp = a->next; tmp; tmp = tmp->next, h++) {
                struct stat in;
                char *p = mx_abs_filename(a->data, tmp->data);
                lstat(p, &in);
                (i == 1) ? m[h] = mx_min(in) : 0;
                (i == 2) ? m[h] = mx_maj(in) : 0;
                free(p);
            }
            res = mx_cooljoin(res, mx_max(inf, m, i));
            (i == 1) ? res = mx_delit_fre(res, ", ") : 0;
            mx_del_strarr(&m);
        }
	}
    else 
        res = mx_cooljoin(res, mx_itoa(inf.st_size));
    return res;
}

