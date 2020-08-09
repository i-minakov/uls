#include "../inc/uls.h"

static char *change(char *tmp) {
	char *r = NULL;

	tmp = mx_replace_substr(tmp, "execute", "search");
    tmp = mx_replace_substr(tmp, "append", "add_subdirectory");
    tmp = mx_replace_substr(tmp, "write", "add_file");
    tmp = mx_replace_substr(tmp, "read", "list");
	char **m = mx_strsplit(tmp, ',');
	buble_s(m);
	for (int i = 0; m[i]; i++) {
		r = mx_delit_fre(r, m[i]);
		m[i + 1] ? r = mx_delit_fre(r, ",") : 0;
	}
	mx_del_strarr(&m);
	free(tmp);
	return r;
}

static char *e_file(char **z) {
	char *res = NULL;
	for (int j = 0; z[j]; j++) {
        if (j == 0 || j == 2 || j == 4 || j == 5) {
            res = mx_delit_fre(res, z[j]);
            if (j == 0)
                res = mx_delit_fre(res, ":");
            else 
				if (j != 5)
                	res = mx_delit_fre(res, " ");
        }
	}
	return res;
}

static char *e_dir(char **z) {
	char *res = NULL;
	res = mx_delit_fre(res, z[0]);
	res = mx_delit_fre(res, ":");
	res = mx_delit_fre(res, z[2]);
	res = mx_delit_fre(res, " ");
	char *tmp = NULL;
	if (mx_get_char_index(z[4], ',')) {
		char **q = mx_strsplit(z[4], ',');
		res = mx_delit_fre(res, q[0]);
		res = mx_delit_fre(res, " ");
		char *w = NULL;
		for (int j = 1; q[j]; j++) {
			w = mx_delit_fre(w, q[j]);
			w = mx_delit_fre(w, ",");
		}
		mx_del_strarr(&q);
		tmp = mx_cooljoin(tmp, w); 
	}
	else 
		tmp = mx_strjoin(tmp, z[4]);
	tmp = mx_delit_fre(tmp, ",");
	tmp = mx_delit_fre(tmp, z[5]);
	res = mx_cooljoin(res, change(tmp));
	return res;
}


static char *flag_e(char *f, struct stat info_p) {
    char *res = NULL;
    char **s = mx_strsplit(f, '\n');
	for (int i = 1; s[i]; i++) {
		char **z = mx_strsplit(s[i], ':');
		res = mx_delit_fre(res, " ");
		res = mx_cooljoin(res, mx_itoa(i - 1));
		res = mx_delit_fre(res, ": ");
		if (MX_ISDIR(info_p.st_mode)) {
			res = mx_cooljoin(res, e_dir(z));
		}
		else 
			res = mx_cooljoin(res, e_file(z));
		if (s[i + 1]) 
				res = mx_delit_fre(res, "\n");
		mx_del_strarr(&z);
	}
	mx_del_strarr(&s);
	return res;
}

char *na_zavod(char *absoluteFileName, struct stat info_p){
	char *res = NULL;
	#ifdef __APPLE__
    char *f = NULL;
    acl_t acl = acl_get_file(absoluteFileName, ACL_TYPE_EXTENDED);
    f = acl_to_text(acl, NULL);
	if (f) {
		res = mx_delit_fre(res, "\n");
    	res = mx_cooljoin(res, flag_e(f, info_p));
		free(f);
	}
	acl_free(acl);
	#endif
	return res;
}







