#include "../inc/uls.h"

static void create_list(char *all, char *dirname, t_list **f) {
    DIR *mydir;
    struct dirent *myfile;
    t_list *f_node = *f;
    bool a = flagfora(all);
    mydir = opendir(dirname);
    if (errno == 13) {
        errno = 0;
        return ;
    }
    while((myfile = readdir(mydir)) != NULL) { 
        if (a == true) {
            f_node->next = mx_create_node(mx_strdup(myfile->d_name));
            f_node = f_node->next;
        }
        else if (myfile->d_name[0] != '.') {
            f_node->next = mx_create_node(mx_strdup(myfile->d_name));
            f_node = f_node->next;
        }
    }
    closedir(mydir);
}

t_list *crate_ls(char *all, char *dirname) {
    t_list *f_node = mx_create_node(mx_strdup(dirname));
    f_node->next = NULL;
    t_list *res = f_node;
    if (readcheck(dirname, all)) { // or opencheck 
        create_list(all, dirname, &f_node);
        if(res->next != NULL)
            file_sort(&res);
    }
    errno = 0;
    return res;
}
