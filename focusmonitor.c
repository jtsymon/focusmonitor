#include <string.h>
#include <stdio.h>
#include <X11/Xlib.h>

int catcher(Display *d, XErrorEvent *e) {
    // avoids terminating on error
    return 0;
}

int main() {
    Display *d = XOpenDisplay(0);
    if (!d) {
        fprintf(stderr, "Could not open display\n");
        return 1;
    }

    XSetErrorHandler(catcher);

    Window root = DefaultRootWindow(d);
    XSelectInput(d, root, PropertyChangeMask);

    XEvent e;
    Window w = 0;
    int revert_to;
    char *atom;

    for (;;) {
        // print current focused window
        XGetInputFocus(d, &w, &revert_to);
        // also listen for events on the active window
        XSelectInput(d, w, PropertyChangeMask);
        printf("%llu\n", (int)w);
        // wait for next event
        do {
            XNextEvent(d, &e);
        } while (
                e.type != PropertyNotify ||
                !(atom = XGetAtomName(d, e.xproperty.atom)) ||
                (
                 strcmp(atom, "_NET_ACTIVE_WINDOW") &&
                 strcmp(atom, "WM_ICON_NAME")
                )
        );
        // stop listening for events on the active window
        if (w != root) {
            XSelectInput(d, w, NoEventMask);
        }
    }
    return 0;
}
