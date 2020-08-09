#ifndef ULS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/acl.h>
#include <time.h>

#include "../libmx/inc/libmx.h"

#define MX_ISEXE(m)      ((m & MX_IFMT) == MX_IFREG && (m & 0111))   /* exe */
#define MX_ISBLK(m)      (((m) & MX_IFMT) == MX_IFBLK)                  /* block special */
#define MX_ISCHR(m)      (((m) & MX_IFMT) == MX_IFCHR)                  /* char special */
#define MX_ISDIR(m)      (((m) & MX_IFMT) == MX_IFDIR)                  /* directory */
#define MX_ISFIFO(m)     (((m) & MX_IFMT) == MX_IFIFO)                  /* fifo or socket */
#define MX_ISREG(m)      (((m) & MX_IFMT) == MX_IFREG)                  /* regular file */
#define MX_ISLNK(m)      (((m) & MX_IFMT) == MX_IFLNK)                  /* symbolic link */
#define MX_ISSOCK(m)     (((m) & MX_IFMT) == MX_IFSOCK)                 /* socket */
#define MX_ISWHT(m)      (((m) & MX_IFMT) == MX_IFWHT)                  /* OBSOLETE: whiteout */

/* File type */
#define MX_IFMT          0170000         /* [XSI] type of file mask */
#define MX_IFIFO         0010000         /* [XSI] named pipe (fifo) */
#define MX_IFCHR         0020000         /* [XSI] character special */
#define MX_IFDIR         0040000         /* [XSI] directory */
#define MX_IFBLK         0060000         /* [XSI] block special */
#define MX_IFREG         0100000         /* [XSI] regular */
#define MX_IFLNK         0120000         /* [XSI] symbolic link */
#define MX_IFSOCK        0140000         /* [XSI] socket */
#define MX_IFWHT         0160000         /* OBSOLETE: whiteout */

/* File mode */
/* Read, write, execute/search by owner */
#define MX_IRWXU         0000700         /* [XSI] RWX mask for owner */
#define MX_IRUSR         0000400         /* [XSI] R for owner */
#define MX_IWUSR         0000200         /* [XSI] W for owner */
#define MX_IXUSR         0000100         /* [XSI] X for owner */
/* Read, write, execute/search by group */
#define MX_IRWXG         0000070         /* [XSI] RWX mask for group */
#define MX_IRGRP         0000040         /* [XSI] R for group */
#define MX_IWGRP         0000020         /* [XSI] W for group */
#define MX_IXGRP         0000010         /* [XSI] X for group */
/* Read, write, execute/search by others */
#define MX_IRWXO         0000007         /* [XSI] RWX mask for other */
#define MX_IROTH         0000004         /* [XSI] R for other */
#define MX_IWOTH         0000002         /* [XSI] W for other */
#define MX_IXOTH         0000001         /* [XSI] X for other */

#define MX_ISUID         0004000         /* [XSI] set user id on execution */
#define MX_ISGID         0002000         /* [XSI] set group id on execution */
#define MX_ISVTX         0001000         /* [XSI] directory restrcted delete */

#define MX_MAJOR(x)        ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
#define MX_MINOR(x)        ((int32_t)((x) & 0xffffff))

typedef struct s_flag {
    int s; 
    int e;
    int R;
    int i;
    int ext;
    int u;
    int C;
    int one;
    int total;
    int flag;
    int l;
} t_flag;

typedef struct s_print {
    int list_size;
    t_flag *flags;
    int max_len[4];
}              t_print;


void its_R(t_list *res, char *c, t_flag *variable);
void its_not_R(int flagforl, t_list *res, t_flag *c, char *all);
bool no_file(char *dirname, int f);
bool perm_den(char *dirname, char *print);
char *start_flags(char *c[]);
int start_words(char *c[]);
void bad_flag(char *flags);
t_list *crate_ls(char *all, char *dirname);
bool opencheck(char *dirname, int start);
void ls_l(t_list *all, t_flag *variable);
t_list *stolb(t_list *sorted);
int flag_check(t_list **all, char *flags, t_flag *variable);
void print_normal(t_list *st, char *name, t_flag *c);
void a_eto_R(char *dirname, char *all, t_flag *c);
char *mx_abs_filename(char *name_dir, char *data);
void mx_print_l(char **res, t_list *list, t_print *p);
char *na_zavod(char *absoluteFileName, struct stat info_p);
int mx_total(t_list *list);
char *flag_s(char *name, t_list *list);
char *flag_i(char *name, t_list *list);
char *find_extend(char *name);
char *mx_link(char *filename, char *absoluteFileName, char str[]);
char *mx_acl_xxatr(char *name);
void mode_to_letters(int mode, char str[]);
void buble_s(char **m);
void sort_check(t_list **list, char *flags);
int data_check(int arg, char *c[], t_flag *variable, int start);
char *mx_size(struct stat inf, char str[], t_list *a);
void mx_print_utils(char **res, t_print *p);

void r_sort(t_list **list);
void file_sort(t_list **list);
void free_list(t_list **list);
void free_list_arr(t_list ***l);
bool flagfora(char *all);
bool readcheck(const char *dirname, char *all);
bool globalcheck(char *dirname, char *print);
bool errcheck(char *dirname);
void sort_list(t_list ***list, char *flags);

bool cmp_utime(char *f1, char *f2);
bool cmp_time(char *f1, char *f2);
bool cmp_blocks(char *f1, char *f2);
char *check(char *str);
t_list *copy_list(t_list *l);

#endif 
