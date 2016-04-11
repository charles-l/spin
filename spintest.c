#include <stdio.h>
#include "spin.h"

const int big_number = 1000000000;

int main(void) {
    spinner *s = spin_new(utf8_pat1, "Working", UTF8_CHAR_WIDTH);
    int x = 0;
    int working = 1;
    while(working) {
        if(x == (big_number * .25)) {
            spin_upd_msg(s, "Part way through"); // update the status message
            spin_drw(s);
        }
        if(x == (big_number * .75)) {
            spin_upd_msg(s, "Getting close now");
            spin_drw(s);
        }
        if(x % 9999999 == 0) // this is just to throttle it a bit
            spin_drw(s);
        if(x++ > big_number)
            working = 0;
    }
    spin_del(s); // cleanup
    printf("Done!\n");
    return 0;
}
