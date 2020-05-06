#include "MainWindow.hpp"

#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QStyleFactory>
#include <QtDebug>

void prepareStyle()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    QColor darkColor = QColor(50, 50, 50);
    QColor disabledColor = QColor(127, 127, 127);
    darkPalette.setColor(QPalette::Window, darkColor);
    darkPalette.setColor(QPalette::WindowText, Qt::gray);
    darkPalette.setColor(QPalette::Base, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::AlternateBase, darkColor);
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
    darkPalette.setColor(QPalette::Button, darkColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);
    qApp->setPalette(darkPalette);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QStringLiteral("qcode"));
    a.setApplicationVersion(QStringLiteral("0.0.1"));
    a.setApplicationDisplayName(QStringLiteral("qcode"));
    prepareStyle();

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
