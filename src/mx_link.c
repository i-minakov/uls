#include "../inc/uls.h"


char *mx_link_name(char *name) {
    char *tmp = mx_strnew(525);
    char *v = tmp;

    readlink(name, tmp, 524);
    tmp = mx_strjoin(" -> ", tmp);
    free(v);
    return tmp;
}

char *mx_link(char *filename, char *absoluteFileName, char str[]) {
	char *res = NULL;
	if (str[0] == 'l') {
		char *lnk = mx_strdup(filename);
		char *lnk_name = mx_link_name(absoluteFileName);
		lnk = mx_delit_fre(lnk, lnk_name);
		res = mx_delit_fre(res, lnk);
		free(lnk_name);
		free(lnk);
	}
	else
		res = mx_delit_fre(res, filename);
	return res;
}
