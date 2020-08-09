#include "../inc/uls.h"

static void to_print(char *dirname) {
    write(2, "uls: ", mx_strlen("uls: "));
    write(2, dirname, mx_strlen(dirname));
    write(2, ": No such file or directory\n", 
        mx_strlen(": No such file or directory\n"));
}

bool no_file(char *dirname, int f){
    DIR *dirdir;
    dirdir = opendir(dirname);
    int res = errno;
    errno = 0;
    if (res == 2 && f == 2) {
        to_print(dirname);
        return false;
    }
    if (res == 2 && f == 1) 
        return false;
    if (res == 0)
        closedir(dirdir);
    return true;
}
