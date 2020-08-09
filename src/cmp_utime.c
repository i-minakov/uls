#include "../inc/uls.h"

bool cmp_utime(char *f1, char *f2) {
    struct stat inf1;
    struct stat inf2;
    lstat(f1, &inf1);
    lstat(f2, &inf2);
    free(f1);
    free(f2);
    return inf1.st_atime < inf2.st_atime;
}
