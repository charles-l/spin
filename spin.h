#ifndef SPIN_H
#define SPIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define UTF8_CHAR_WIDTH 3

// if you want to add new patterns, put them here (make sure they're utf8)
const char utf8_pat1[]  = "⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏";
const char utf8_pat2[]  = "⠋⠙⠚⠞⠖⠦⠴⠲⠳⠓";
const char utf8_pat3[]  = "⠄⠆⠇⠋⠙⠸⠰⠠⠰⠸⠙⠋⠇⠆";
const char utf8_pat4[]  = "⠋⠙⠚⠒⠂⠂⠒⠲⠴⠦⠖⠒⠐⠐⠒⠓⠋";
const char utf8_pat5[]  = "⠁⠉⠙⠚⠒⠂⠂⠒⠲⠴⠤⠄⠄⠤⠴⠲⠒⠂⠂⠒⠚⠙⠉⠁";
const char utf8_pat6[]  = "⠈⠉⠋⠓⠒⠐⠐⠒⠖⠦⠤⠠⠠⠤⠦⠖⠒⠐⠐⠒⠓⠋⠉⠈";
const char utf8_pat7[]  = "⠁⠁⠉⠙⠚⠒⠂⠂⠒⠲⠴⠤⠄⠄⠤⠠⠠⠤⠦⠖⠒⠐⠐⠒⠓⠋⠉⠈⠈";
const char ascii_pat1[] = ".oOo.";
const char ascii_pat2[] = "x+ ";
const char ascii_pat3[] = ".  ";
const char ascii_pat4[] = "-= ";

typedef struct spinner {
    const char *c;
    const char *pat;
    char *msg;
    int charwidth;
} spinner;

#define CSI "\e["

static void showcur(int show) {
    show ? fputs(CSI "?25h", stdout) : fputs(CSI "?25l", stdout);
}

spinner *spin_new(const char *pat, char *msg, int charwidth) {
    spinner *s = malloc(sizeof(spinner));
    s->pat = pat;
    s->c = s->pat;
    s->msg = msg;
    s->charwidth = charwidth;
    showcur(0);
    return s;
}

void spin_clr(spinner *s) {
    fflush(stdout);
    for(int i = strlen(s->msg) + 2; i > 0; i--)
        printf("\b \b");
}

void spin_drw(spinner *s) {
    spin_clr(s);
    printf("%s ", s->msg);
    for(int i = 0; i < s->charwidth; i++)
        putchar(s->c[i]);
    if((s->c += s->charwidth)[1] == '\0') s->c = s->pat;
}

void spin_upd_msg(spinner *s, char *msg) {
    spin_clr(s);
    s->msg = msg;
}

void spin_del(spinner *s) {
    spin_clr(s);
    showcur(1);
    free(s);
}

#endif // SPIN_H
