
#include "../inc/uls.h"

bool errcheck(char *dirname){
    DIR *dir;
    struct stat stbuf;
    if (mx_get_substr_index(dirname, "/dev/fd/3") == 1 ||
        mx_strcmp(dirname, "/dev/fd/3") == 0) {
        errno = 0;
        return false;
    }
    if (lstat(dirname, &stbuf) == -1){
        errno = 0;
        return false;
    }
    if (S_ISDIR(stbuf.st_mode)) {
        dir = opendir(dirname);
        if (dir == NULL) {
            errno = 0;
            return false;
        }  
    else
        closedir(dir);
    }
    return true;   
}
