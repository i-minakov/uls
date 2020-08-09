#include "../inc/uls.h"

static int termspaces(int len) {
    int res, tmp; 
    if(len % 8 == 0) return 8;
    tmp = len - 8;
    if (tmp < 0)
        res = 8 - len;
    else {
        while (tmp > 8)
            tmp = tmp - 8;
        res = 8 - tmp;
    }
    return res;
}

static int maxlen(t_list *sorted, int count) { // bez golovy 
    int maxs[count];
    for (int i = 0; i < count; i++, sorted = sorted->next)
        maxs[i] = mx_strlen(sorted->data);
    
    for (int i = 0; i < count ; i++) {
        for (int j = 0; j < count ; j++) {
            if (maxs[i] > maxs[j]) {
                int a = maxs[i];
                maxs[i] = maxs[j];
                maxs[j] = a;
            }
        }
    }
    return maxs[0];
}

static void get_s(t_list *so, t_list **n, int j, int r, int c) {
    t_list *new = *n;
     t_list *tmp = so;
        for (int i = 0; i < j; i++)
            tmp = tmp->next;
        char *che = check(tmp->data);
        new->data = mx_delit_fre(new->data, che);
        t_list *newtmp = so;
        if (j + r < c) {
            int maxword = maxlen(newtmp, c) + termspaces(maxlen(newtmp, c)); 
            int space = maxword - mx_strlen(tmp->data);
            for (int k = 0; k < space; k++)
                new->data = mx_delit_fre(new->data, " ");
        }
        free(che);
        che = NULL;
}

static t_list *newlist(t_list *sorted, int count, int rows){ // bez golovy
    t_list *new = mx_create_node(NULL);
    t_list *res = new;
    int notn = 0;;
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < count; j+= rows) {
            get_s(sorted,  &new, j, rows, count);
            notn++;
        }
        if (notn != count) {
            new->next = mx_create_node(NULL);
            new = new->next;
        }
    }
    return res;
}

t_list *stolb(t_list *sorted){ //перенос в столбцы
    int rows, cols;
    int count = 0;
    if(sorted->next == NULL) {
        char *emp = mx_strdup(sorted->data);
        t_list *empty = mx_create_node(emp);
        return empty;
    }
    for (t_list *tmp = sorted->next; tmp; tmp = tmp->next) 
        count++;
    int maxword = maxlen(sorted->next, count) + termspaces(maxlen(sorted->next, count)); 
    struct winsize termlen;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &termlen);
    if (!isatty(1))
        cols = 79 / maxword;
    else 
        cols = termlen.ws_col / maxword;
    rows = count / cols;
    if (count % cols != 0)
        rows++;
    t_list *res = newlist(sorted->next, count, rows);
    return res;
}



