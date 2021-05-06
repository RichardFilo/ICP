#include "mainwindow.h"


#include <QApplication>
#include <QPainter>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication ICPapp(argc, argv);

    MainWindow AppWindow;
    AppWindow.show();

    return ICPapp.exec();
}
