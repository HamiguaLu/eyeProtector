#include "mainwindow.h"
#include <QApplication>


#include <X11/Xlib.h>

#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
#define _NET_WM_STATE_ADD           1    /* add/set property */
#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */


// change a window's _NET_WM_STATE property so that it can be kept on top.
// @display: x11 display singleton.
// @xid    : the window to set on top.
Status x11_window_set_on_top (Display* display, Window xid)
{
    XEvent event;
    event.xclient.type = ClientMessage;
    event.xclient.serial = 0;
    event.xclient.send_event = True;
    event.xclient.display = display;
    event.xclient.window  = xid;
    event.xclient.message_type = XInternAtom (display, "_NET_WM_STATE", False);
    event.xclient.format = 32;

    event.xclient.data.l[0] = _NET_WM_STATE_ADD;
    event.xclient.data.l[1] = XInternAtom (display, "_NET_WM_STATE_ABOVE", False);
    event.xclient.data.l[2] = 0; //unused.
    event.xclient.data.l[3] = 0;
    event.xclient.data.l[4] = 0;

    return XSendEvent (display, DefaultRootWindow(display), False,
                       SubstructureRedirectMask|SubstructureNotifyMask, &event);
}





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setWindowFlags(Qt::FramelessWindowHint);
    Display* display = XOpenDisplay (NULL);

    WId wid = w.winId();
    x11_window_set_on_top (display, wid);

    XFlush (display); //for simplicity, no event loops here.


    w.show();

    int ret = a.exec();
    XCloseDisplay (display);
    return ret;
}
