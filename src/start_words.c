#include "../inc/uls.h"

int start_words(char *c[]) {
    int j = 0;
    for(int i = 1; c[i]; i++){
        if (c[i][0] == '-')
            j++;
    }
    return j;
}
