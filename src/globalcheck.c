#include "../inc/uls.h"

bool globalcheck(char *dirname, char *print){
    DIR *dirdir;
    dirdir = opendir(dirname);
    int res = errno;
    if (res == 2) {
        write(2, "uls: ", mx_strlen("uls: "));
        write(2, dirname, mx_strlen(dirname));
        write(2, ": No such file or directory\n", 
            mx_strlen(": No such file or directory\n"));
        errno = 0;
        return false;
    }
    if (res == 13) {
        write(2, "uls: ", mx_strlen("uls: "));
        write(2, print, mx_strlen(print));
        write(2, ": Permission denied\n", 
            mx_strlen(": Permission denied\n"));
        errno = 0;
        return false;
    }
    closedir(dirdir);
    return true;
}
