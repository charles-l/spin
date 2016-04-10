#include <stdio.h>
#include "spin.h"

int main(void) {
    spinner *s = spin_new(pat1, "Working");
    int x = 0;
    int working = 1;
    while(working) {
        if(x == 399999999)
            spin_drw_msg(s, "Part way through");
        if(x == 699999999)
            spin_drw_msg(s, "Getting close now");
        if(x % 9999999 == 0) // this is just to throttle it a bit
            spin_drw(s);
        if(x++ >= 999999999)
            working = 0;
    }
    spin_clr(s);
    printf("Done!\n");
    return 0;
}
