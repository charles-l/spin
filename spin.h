#ifndef SPIN_H
#define SPIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char pat1[] = "⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏";
const char pat2[] = "⠋⠙⠚⠞⠖⠦⠴⠲⠳⠓";
const char pat3[] = "⠄⠆⠇⠋⠙⠸⠰⠠⠰⠸⠙⠋⠇⠆";
const char pat4[] = "⠋⠙⠚⠒⠂⠂⠒⠲⠴⠦⠖⠒⠐⠐⠒⠓⠋";
const char pat5[] = "⠁⠉⠙⠚⠒⠂⠂⠒⠲⠴⠤⠄⠄⠤⠴⠲⠒⠂⠂⠒⠚⠙⠉⠁";
const char pat6[] = "⠈⠉⠋⠓⠒⠐⠐⠒⠖⠦⠤⠠⠠⠤⠦⠖⠒⠐⠐⠒⠓⠋⠉⠈";
const char pat7[] = "⠁⠁⠉⠙⠚⠒⠂⠂⠒⠲⠴⠤⠄⠄⠤⠠⠠⠤⠦⠖⠒⠐⠐⠒⠓⠋⠉⠈⠈";

typedef struct spinner {
    const char *c;
    const char *pat;
    char *msg;
} spinner;

#define CSI "\e["

static void showcur(int show) {
    show ? fputs(CSI "?25h", stdout) : fputs(CSI "?25l", stdout);
}

spinner *spin_new(const char *pat, char *msg) {
    spinner *s = malloc(sizeof(spinner));
    s->pat = pat;
    s->c = s->pat;
    s->msg = msg;
    showcur(0);
    return s;
}

void spin_drw(spinner *s) {
    fflush(stdout);
    for(int i = strlen(s->msg) + 2; i > 0; i--)
        putchar('\b');
    printf("%s ", s->msg);
    printf("%c%c%c", s->c[0], s->c[1], s->c[2]);
    if((s->c += 3)[1] == '\0') s->c = s->pat;
}

void spin_drw_msg(spinner *s, char *msg) {
    spin_drw(s);
    s->msg = msg;
}

void spin_clr(spinner *s) {
    for(int i = strlen(s->msg) + 2; i > 0; i--)
        printf("\b \b");
    showcur(1);
    free(s);
}

#endif // SPIN_H
