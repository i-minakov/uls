#include "../inc/uls.h"

char *mx_abs_filename(char *name_dir, char *data) {
	char *p = NULL;
	if (mx_get_char_index(data, '/') >= 0 && name_dir == NULL) 
		return mx_strdup(data);
	if (name_dir == NULL)
		p = mx_delit_fre(p, ".");
	else 
		p = mx_delit_fre(p, name_dir);
	p = mx_delit_fre(p, "/");
	p = mx_delit_fre(p, data);
	return p;
}
