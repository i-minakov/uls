#include "../inc/uls.h"

bool opencheck(char *dirname, int start) {
    errno = 0;
    DIR *dirdir;
    dirdir = opendir(dirname);
    if (errno == 13) {
        errno = 0;
        return true;
    }
    if (dirdir == NULL) {
        errno = 0;
        return false;
    }
    struct stat i;
    lstat(dirname, &i);
    if (!MX_ISDIR(i.st_mode) && start == 2) {
        errno = 0;
        closedir(dirdir);
        return false;
    }
    errno = 0;
    closedir(dirdir);
    return true;
}
