#include "../inc/uls.h"

static void to_print(char *m) {
    write(2, "uls: ", 5);
    write(2, m, mx_strlen(m));
    write(2, ": Permission denied\n", 20);
}

static bool pusto(char *p) {
    int j = 0;
    for (; p[j]; j++);
    if (p[j - 1] == p[0] && p[j - 1] == '/') {
        to_print("");
        free(p);
        return false;
    }
    return true;
}

bool perm_den(char *dirname, char *print) {
    DIR *dirdir;
    dirdir = opendir(dirname);
    int res = errno;
    errno = 0;
    if (res == 13) {
        char *p = mx_abs_filename(NULL, print);
        int j = 0;
        if (!pusto(p))
            return false;
        char **m = mx_strsplit(p, '/');
        for (; m[j]; j++);
        to_print(m[j - 1]);
        mx_del_strarr(&m);
        free(p);
        return false;
    }
    else
        closedir(dirdir);
    return true;
}
