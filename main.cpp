#include "MainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QStringLiteral("qcode"));
    a.setApplicationVersion(QStringLiteral("0.0.1"));
    a.setApplicationDisplayName(QStringLiteral("qcode"));
    MainWindow w;
    w.show();
    return a.exec();
}
