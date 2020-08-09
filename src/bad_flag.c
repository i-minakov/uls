#include "../inc/uls.h"

void bad_flag(char *flags) {
    for (int i = 1; flags[i]; i++) {
        if (flags[i] == 'R' ||flags[i] == 'l' || flags[i] == 'a' 
            || flags[i] == 's' || flags[i] == 'i' || flags[i] == '@'
                || flags[i] == 'u'|| flags[i] == 'e' || flags[i] == '1'
                    || flags[i] == 'C' || flags[i] == 'S' 
                        || flags[i] == 't' || flags[i] == 'r') 
                    continue;
        else {
            write(2, "uls: illegal option -- ", 23);
            write(2, &flags[i], 1);
            write(2, "\nusage: uls [-CRSaeilrstu@1] [file ...]\n", 39);
            exit(1);
        }
    }
}

