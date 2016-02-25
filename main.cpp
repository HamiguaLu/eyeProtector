
#include <QApplication>


#include <X11/Xlib.h>

#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
#define _NET_WM_STATE_ADD           1    /* add/set property */
#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */


// change a window's _NET_WM_STATE property so that it can be kept on top.
// @display: x11 display singleton.
// @xid    : the window to set on top.
void x11_window_set_on_top ( Window xid)
{
    Display* display = XOpenDisplay (NULL);
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

    XSendEvent (display, DefaultRootWindow(display), False,
                       SubstructureRedirectMask|SubstructureNotifyMask, &event);

    XFlush (display);

    XCloseDisplay (display);
}

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


bool isCfgExist()
{
    const char *homedir;
    if ((homedir = getenv("XDG_CONFIG_HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

   char cfgFileName[1024];
   sprintf(cfgFileName,"%s/.config/autostart/eyeProtector.desktop",homedir);
   if (0 == access(cfgFileName, 0)) {
       return true;
   }

   return false;
}


void createAutoStartCfg(bool bAutoStart)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
          return;
    }

    const char *homedir;
    if ((homedir = getenv("XDG_CONFIG_HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    char cmd[1024];
    sprintf(cmd,"mkdir %s/.config",homedir);
    system(cmd);
    sprintf(cmd,"mkdir %s/.config/autostart",homedir);
    system(cmd);

   char cfgFileName[1024];
   sprintf(cfgFileName,"%s/.config/autostart/eyeProtector.desktop",homedir);
   FILE *fcfg = fopen(cfgFileName,"w+");
   fprintf(fcfg,"[Desktop Entry]\n");
    fprintf(fcfg,"Exec=%s/eyeProtector\n",cwd);
    fprintf(fcfg,"Icon=%s/Eye_small.png\n",cwd);
    fprintf(fcfg,"Type=Application\n");
    fprintf(fcfg,"Terminal=false\n");
    fprintf(fcfg,"Name=Eye Protector\n");
    fprintf(fcfg,"InitialPreference=9\n");
    if (bAutoStart)
    {
        fprintf(fcfg,"X-GNOME-Autostart-enabled=true\n");
    }

    fclose(fcfg);

}



#include "qresttimecounter.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.show();*/

    QRestTimeCounter *m_restInfoDlg = new QRestTimeCounter();
    x11_window_set_on_top(m_restInfoDlg->winId());
     m_restInfoDlg->setWindowFlags(Qt::FramelessWindowHint);
     m_restInfoDlg->show();

    return a.exec();

}
