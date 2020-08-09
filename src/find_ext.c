#include "../inc/uls.h"

static char *add_space(char *c, int num) {
    char *s = mx_strdup(c);
    char *v = mx_itoa(num);
    for (int i = 0; ; i++) {
        int j = (mx_strlen(s) + mx_strlen(v)) % 4;
        int x = ((mx_strlen(s) + mx_strlen(v)) / 4) % 2;
        if (j == 0 && x == 1 && i != 0)
            break;
        s = mx_delit_fre(s, " ");
    }
	free(v);
	free(c);
    return s;
}

static char *for_ext(char **s, char *name) {
	char *res = NULL;
    #ifdef __APPLE__
	for (int i = 0; s[i]; i++) {
		ssize_t gxattr = getxattr(name, s[i], NULL, 0, 0, XATTR_NOFOLLOW);
		s[i] = mx_backjoin("\t", s[i]);
		char *tmp = mx_itoa((int)gxattr);
		s[i] = add_space(s[i], (int)gxattr);
		s[i] = mx_delit_fre(s[i], tmp);
		res = mx_delit_fre(res, s[i]);
		s[i+1] != NULL ? res = mx_delit_fre(res, "\n") : 0;
		free(tmp);
	}
    #endif
	return res;
}

char *find_extend(char *name) {
	char *res = NULL;
    #ifdef __APPLE__
    static char tmp[512];
    ssize_t xattr = listxattr(name, tmp, 512, XATTR_NOFOLLOW);
    ssize_t gxattr = getxattr(name, tmp, NULL, 0, 0, XATTR_NOFOLLOW);
    if (gxattr == -1)
        return NULL;
    for (int i = 0; i < xattr - 1; i++)
        if (tmp[i] == '\0')
            tmp[i] = '\n';
    char **s = mx_strsplit(tmp, '\n');
	res = mx_delit_fre(res, "\n");
	char *ex = for_ext(s, name);
	res = mx_delit_fre(res, ex);
	free(ex);
	mx_del_strarr(&s);
    #endif
    return res;
}
