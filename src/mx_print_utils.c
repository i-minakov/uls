#include "../inc/uls.h"

static int mx_find_maxlen(char **res, int index, int len) {
    int r = -1;
    for (int i = 0; i < len; i++) {
        char **buf = mx_strsplit(res[i], '*');
        if (mx_strlen(buf[index]) > r){ 
            if (index == 4 && mx_get_char_index(buf[index], ',') 
                && mx_strlen(buf[index]) > 10)
                r = r*1;
            else 
                r = mx_strlen(buf[index]);
        }
        mx_del_strarr(&buf);
    }
    return r;
}

void mx_print_utils(char **res, t_print *p) {
    for (int i = 1; i < 5; i++)
        p->max_len[i - 1] = mx_find_maxlen(res, i, p->list_size);
}
