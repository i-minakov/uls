#include "../inc/uls.h"

char *check(char *str){
    char *res = NULL;
    res = mx_strdup(str);
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\a' || str[i] == '\b' 
            || str[i] == '\t' || str[i] == '\n'
                || str[i] == '\v' || str[i] == '\f'
                    || str[i] == '\r')
                        res[i] = '?';
    }
    return res;
}
