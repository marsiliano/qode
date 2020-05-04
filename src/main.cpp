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
        const auto f = a.arguments()[1];
        auto path = QDir::currentPath() + QDir::toNativeSeparators("/");
        if (f != QStringLiteral(".")) {
            path += f;
        }

        QFileInfo fileInfo(path);
        if (fileInfo.exists()) {
            w.open(fileInfo.absoluteFilePath());
        }
    }

    w.show();
    return a.exec();
}
