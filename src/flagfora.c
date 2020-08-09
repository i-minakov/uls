#include "../inc/uls.h"

bool flagfora(char *all) {
    if (all != NULL) {
    if (all[0] == '-' && mx_get_char_index(all, 'a') > 0)
        return true;
    }
    return false;
}
