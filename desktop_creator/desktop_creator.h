#ifndef DESKTOP_CREATOR_H
#define DESKTOP_CREATOR_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDirIterator>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QCoreApplication>

class Desktop_Creator
{
    public:
        Desktop_Creator();

        static bool createDesktop();
        static bool deleteDesktop();
    private:
        static QString getDesktopName();
        static QString getDesktopVersion();
        static QString getDesktopIcon();
};

#endif // DESKTOP_CREATOR_H
