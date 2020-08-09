#include "../inc/uls.h"

bool readcheck(const char *dirname, char *all) {
    DIR *dirdir;
    dirdir = opendir(dirname);
    if (dirdir == NULL) {
        errno = 0;
        return false;
    }
    struct dirent *read;
    while((read = readdir(dirdir)) != NULL){
        if (mx_strcmp(read->d_name, ".") != 0 
            || mx_strcmp(read->d_name, "..") != 0) {
            if (!flagfora(all) && mx_get_char_index(read->d_name, '.') == 0)
                continue;
            else {
                closedir(dirdir);
                return true;
            }
        }
    }
    closedir(dirdir);
    return false;
}
