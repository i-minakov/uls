#include "../inc/uls.h"

char *mx_acl_xxatr(char *name) {
	char *res = NULL;
	#ifdef __APPLE__
	ssize_t xtr  = listxattr(name, NULL, 0, XATTR_NOFOLLOW);
	acl_t acl = acl_get_file(name, ACL_TYPE_EXTENDED);
	if (xtr > 0) {
		res = mx_delit_fre(res, "@");
		if (acl) {
            acl_free(acl);
            acl = NULL;
        }
    }
    else if (acl) {
		res = mx_delit_fre(res, "+");
        acl_free(acl);
        acl = NULL;
    }
	else 
		res = mx_delit_fre(res, " ");
	#endif
	return res;
}

