#include "../inc/uls.h"


static char *uid_to_name(uid_t uid) {
	struct passwd *getpwuid();
    struct passwd *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL){
		char *u = mx_itoa(uid);
		mx_strcpy(numstr, u);
		free(u);
		return numstr;
	}
	else return pw_ptr->pw_name;
}


static char *gid_to_name(gid_t gid) {
	struct group *getgrgid();
    struct group *grp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL){
		char *g = mx_itoa(gid);
		mx_strcpy(numstr, g);
		free(g);
		return numstr;
	}
	else return grp_ptr->gr_name;
}


static char *mx_time(struct stat info_p, t_flag *c) {
	char *res = mx_strnew(12);
	int k = 0;
	time_t last = info_p.st_mtime;
    time_t now = time(NULL);
	char *s = NULL;
	(c->u == 1) ? s = ctime(&info_p.st_atime) : 0;
	(c->u == 0) ? s = ctime(&info_p.st_mtime) : 0;
	if ((now - last) > (31536000 / 2)) {
		for (int i = 4; i < mx_strlen(s) - 1; i++)
			if (i < 11 || i > 18) {
				res[k] = s[i];
				k++;
			}
	}
	else {
		for (int i = 4; i < mx_strlen(s) - 1; i++)
			if (i < 16) {
				res[k] = s[i];
				k++;
			}
	}
	return res;
}


static char *show_file_info(char *filename, struct stat info_p,
	char *absoluteFileName, t_flag *c, t_list *a) {	
	char *res = NULL;
	char str[11] = "----------";
	mode_to_letters(info_p.st_mode, str); 
	res = mx_strjoin(res, str);
	res = mx_cooljoin(res, mx_acl_xxatr(absoluteFileName));
	res = mx_delit_fre(res, "*");
	res = mx_cooljoin(res, mx_itoa((int)info_p.st_nlink));
	res = mx_delit_fre(res, "*");
	res = mx_delit_fre(res, uid_to_name(info_p.st_uid));
	res = mx_delit_fre(res, "*");
	res = mx_delit_fre(res, gid_to_name(info_p.st_gid));
	res = mx_delit_fre(res, "*");
	res = mx_cooljoin(res , mx_size(info_p, str, a));
	res = mx_delit_fre(res, "*");
	res = mx_cooljoin(res, mx_time(info_p, c));
	res = mx_delit_fre(res, "*");
	res = mx_delit_fre(res, filename);
	return res;
}


void ls_l(t_list *all, t_flag *variable) {
	char *name = NULL;
	if (all->data != NULL)
		name = all->data;
	int i = 0;
	char **res = (char **)malloc(sizeof(char *) * 
		(mx_list_size(all)));
	res[mx_list_size(all) - 1] = NULL;
	t_print *pr = (t_print *)malloc(sizeof(t_print));
	for (t_list *tmp = all->next; tmp; tmp = tmp->next, i++) {
		char *p = mx_abs_filename(name, tmp->data);
		struct stat info;
		lstat(p, &info); 
		res[i] = show_file_info(tmp->data, info, p, variable, all);
		res[i] = mx_delit_fre(res[i], "*");
		if (variable->ext == 1)
			res[i] = mx_cooljoin(res[i], find_extend(p));
		if (variable->e == 1)
			res[i] = mx_cooljoin(res[i], na_zavod(p, info));
		free(p);
	}
	pr->list_size = mx_list_size(all) - 1;
	pr->flags = variable;
	mx_print_l(res, all, pr);
	mx_del_strarr(&res);
	free(pr);
}

