#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub)
{
    if (str == NULL || sub == NULL) return -2;
    int r = 0, res = 0;
    for (int i = 0; str[i]; i++) {
        res = i;
        if (str[i] == sub[0]) {
            for (int j = 1, k = i + 1; j < mx_strlen(sub); j++, k++) {
                if (str[k] == sub[j]) r++;
            }
            if (r == mx_strlen(sub) - 1) return res;
        }
    }
    return -1;
}
