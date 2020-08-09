#include "../inc/uls.h"

int mx_total(t_list *list) {
	int res = -1;
	char *name = list->data;
	if (name == NULL || list->next == NULL)
		return res;
	for (t_list *t = list->next; t; t = t->next) {
		char *p = mx_abs_filename(name, t->data);
		struct stat in;
		lstat(p, &in);
		res += in.st_blocks;
		free(p);
		p = NULL;
	}
	return res + 1;
}
