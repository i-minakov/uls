#include "../inc/uls.h"

void its_not_R(int flagforl, t_list *res, t_flag *c, char *all) {
    if((flagforl == 0 || flagforl == -1 || 
        (flagforl == 1 && c->one == 1 && (mx_get_char_index(all, 'l') - 
            mx_get_char_index(all, '1') < 0))) && res != NULL) {
        if (((c->one != 1 || res->next == NULL) 
            && isatty(1)) || (!isatty(1) && c->C == 1)) {
            t_list *r = stolb(res);
            print_normal(r, res->data, c);
            free_list(&r);
        }
        else 
            print_normal(res->next, res->data, c);
        errno = 0;
    }
}

