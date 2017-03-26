#ifndef UTIL
#define UTIL
#include <QDesktopWidget>
#include <QApplication>
namespace util{

void centerize(QWidget* window)
{
    QDesktopWidget* d = QApplication::desktop();
    window->move((d->width()-window->width())/2, (d->height()-window->height())/2);
}

}



#endif
