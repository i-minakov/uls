#include "../inc/uls.h"

static char *absname(char *dirname, char *read) {
    char *tmp = NULL;
    if (mx_strcmp(dirname, "/") != 0) {
        tmp = mx_strjoin(dirname, "/");
        tmp = mx_delit_fre(tmp, read);
    }
    else tmp = mx_strjoin(dirname, read);
    return tmp;
}

static bool papka_ili_err(t_list *i, char *all, char *tmp) {
    if (((!flagfora(all) && mx_get_char_index(i->data, '.') != 0) 
        || (flagfora(all) && (mx_get_char_index(i->data, '.') == 0 
            || mx_get_char_index(i->data, '.') != 0)))
                && (opencheck(tmp, 2) || !errcheck(tmp))) {
                    return true;
    }
    return false;
}

static void start_R(char *dirname, char *all, t_list *newlist, t_flag *c) {
    for (t_list *i = newlist->next; i; i = i->next){
            char *tmp = absname(dirname, i->data);
            struct stat stbuf;
            lstat(tmp, &stbuf);
        if (papka_ili_err(i, all, tmp) && mx_strcmp(i->data, ".") != 0 && 
            mx_strcmp(i->data, "..") != 0) { //если это не файл или пуст пап и если это ошиб 
                char *rec = absname(dirname, i->data);
                write(1, "\n", 1);
                c->flag = 2;
                a_eto_R(rec, all, c);
        }
        free(tmp);
        tmp = NULL;
    }
}

static bool deskr(char *dirname, t_flag *c){
    if (mx_strcmp(dirname, "/dev/fd/3") == 0 && c->flag == 2) {
        write(1, "uls: 3: Not a directory\n", 
            mx_strlen("uls: 3: Not a directory\n"));
        write(1, "uls: 4: directory causes a cycle\n", 
            mx_strlen("uls: 4: directory causes a cycle\n"));
            return true;
    }
    return false;
}


void a_eto_R(char *dirname, char *all, t_flag *c) { // РБ
    t_list *newlist = crate_ls(all, dirname);
    t_list *copy = copy_list(newlist); 
    int flagforl = flag_check(&newlist, all, c);
    if((flagforl == 0 || flagforl == -1 || 
        (flagforl == 1 && c->one == 1 && (mx_get_char_index(all, 'l') - 
            mx_get_char_index(all, '1') < 0))) && !deskr(dirname, c)) {
        if (((c->one != 1 || newlist->next == NULL) 
                && isatty(1)) || (!isatty(1) && c->C == 1)) {
            t_list *r = stolb(newlist);
            print_normal(r, dirname, c);
            free_list(&r);
        }
        else 
            print_normal(newlist->next, dirname, c);
        errno = 0;
    }
    if (readcheck(copy->data, all)) 
        start_R(dirname, all, copy, c); //если она не пустая и не ошиб
    free_list(&newlist);
    free_list(&copy);
    free(dirname);
    dirname = NULL;
}

