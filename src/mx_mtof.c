#include "../inc/uls.h"

void mode_to_letters(int mode, char str[]) {	
	MX_ISDIR(mode) ? str[0] = 'd' : 0;
	MX_ISCHR(mode) ? str[0] = 'c' : 0;
	MX_ISBLK(mode) ? str[0] = 'b' : 0;
	MX_ISLNK(mode) ? str[0] = 'l' : 0;
	(mode & MX_IRUSR) ? str[1] = 'r' : 0;
	(mode & MX_IWUSR) ? str[2] = 'w' : 0;
	(mode & MX_IXUSR) ? str[3] = 'x' : 0;
	(mode & MX_IRGRP) ? str[4] = 'r' : 0;
	(mode & MX_IWGRP) ? str[5] = 'w' : 0;
	(mode & MX_IXGRP) ? str[6] = 'x' : 0;
	(mode & MX_IROTH) ? str[7] = 'r' : 0;
	(mode & MX_IWOTH) ? str[8] = 'w' : 0;
	(mode & MX_IXOTH) ? str[9] = 'x' : 0;
}
