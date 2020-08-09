#include "../inc/uls.h"

static void r_sort_formas(t_list ***list) {
    t_list **t = *list;
    int count = 0;
    int chan = 0;
    int sr;
    for (; t[count]; count++);
    if(count%2 > 0)
        sr = (count/2) + 1;
    else
        sr = count/2;
    while (chan < sr) {
            count--;
            t_list *tmp = t[chan];
            t[chan] = t[count];
            t[count] = tmp;
            chan++;
    }
}

static void sort_at(t_list ***list, bool (*cmp)(char *, char *), int len) {
    t_list **res = *list;
    int i = 1;
    while (i) { 
        i = 0;
        for (int j = 0; j < len - 1; j++) {
            if (cmp(mx_abs_filename(NULL,res[j]->data), 
                    mx_abs_filename(NULL, res[j + 1]->data))) {
                t_list *tmp = res[j];
                res[j] = res[j + 1];
                res[j + 1] = tmp;
                i = 1;
            }
        }
    }
}

void other_sort(t_list ***list, char *flags, int len) {
    if (mx_get_char_index(flags, 'S') >= 0)
        sort_at(list, cmp_blocks, len);
    else {
        if (mx_get_char_index(flags, 't') >= 0) {
            if (mx_get_char_index(flags, 'u') >= 0)
                sort_at(list, cmp_utime, len);
            else 
                sort_at(list, cmp_time, len);
        }
    }
    if (mx_get_char_index(flags, 'r') >= 0) {
        r_sort_formas(list);
    }
}

void sort_list(t_list ***list, char *flags) {
    t_list **res = *list;
    int len = 0;
    for (; res[len]; len++);
    int i = 1;
    while (i) { 
        i = 0;
        for (int j = 0; j < len - 1; j++) {
            if (mx_strcmp(res[j]->data, res[j + 1]->data) > 0) {
                t_list *tmp = res[j];
                res[j] = res[j + 1];
                res[j + 1] = tmp;
                i = 1;
            }
        }
    }
    other_sort(list, flags, len);
}


