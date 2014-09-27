#include <string.h>
#include <stdio.h>
#include <X11/Xlib.h>

int main() {
    Display *d = XOpenDisplay(0);
    if (!d) {
        fprintf(stderr, "Could not open display\n");
        return 1;
    }

    XSelectInput(d, DefaultRootWindow(d), PropertyChangeMask);

    XEvent e;
    Window w;
    int revert_to;

    for (;;) {
        // print current focused window
        XGetInputFocus(d, &w, &revert_to);
        printf("%llu\n", (int)w);
        // wait for next event
        do {
            XNextEvent(d, &e);
        } while (e.type != PropertyNotify || strcmp(XGetAtomName(d, e.xproperty.atom), "_NET_ACTIVE_WINDOW"));
    }
    return 0;
}
