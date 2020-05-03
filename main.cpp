#include "MainWindow.hpp"

#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QStringLiteral("qcode"));
    a.setApplicationVersion(QStringLiteral("0.0.1"));
    a.setApplicationDisplayName(QStringLiteral("qcode"));

    QCommandLineParser parser;
    parser.setApplicationDescription(QObject::tr("Simple editor for general purpose use."));
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(a);

    MainWindow w;

    if (a.arguments().size() > 1) {
        auto f = a.arguments()[1];
        QFileInfo fileInfo(QDir::currentPath() + QDir::toNativeSeparators("/") + f);
        if (fileInfo.isFile() && fileInfo.exists()) {
            w.open(fileInfo);
        }
    }

    w.show();
    return a.exec();
}
