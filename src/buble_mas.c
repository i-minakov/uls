#include "../inc/uls.h"

void buble_s(char **m) {
	int f = 1;
	while (f) {
		f = 0;
		for (int i = 0; m[i + 1]; i++) {
			if (mx_strcmp(m[i], m[i + 1]) > 0) {
				char *t = m[i];
				m[i] = m[i + 1];
				m[i + 1] = t;
				f = 1;
			}
		}
	}
}
