#include "../inc/uls.h"

char *start_flags(char *c[]) {
    char *res = NULL;
    res = mx_strjoin(res, "-");
    for(int i = 1; c[i]; i++){
        if (c[i][0] == '-'){
            char **tmp = mx_strsplit(c[i], '-');
            res = mx_delit_fre(res, tmp[0]);
            mx_del_strarr(&tmp);
        }
    }
    return res;
}
