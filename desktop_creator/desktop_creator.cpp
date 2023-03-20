#include "desktop_creator.h"

Desktop_Creator::Desktop_Creator()
{

}

bool Desktop_Creator::createDesktop()
{
    QStringList args;
    QString desktop_name = getDesktopName() + ".desktop";
    QString desktop_version = getDesktopVersion();
    QString desktop_file_path = QDir::homePath() + "/.local/share/applications/" + desktop_name;
    QString exec_path = QCoreApplication::applicationFilePath();
    if(QFile::exists(desktop_file_path))
    {
        qDebug() << "exist";
        QFile tmp_desktop_file(desktop_file_path);
        tmp_desktop_file.open(QIODevice::ReadOnly);
        QString existing_version; 
        while(!tmp_desktop_file.atEnd())
        {
            QString line = tmp_desktop_file.readLine();
            if(line.contains("Version"))
            {
                existing_version = line.mid(8);
                existing_version.remove('\n');
                break;
            }
        }
        QMessageBox::StandardButton ret = QMessageBox::warning(nullptr, "警告", "版本" + existing_version + "已存在, 是否覆盖该版本?", QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::No) return false;
    }
    args.push_back("[Desktop Entry]");
    args.push_back("Version=" + desktop_version);
    args.push_back("Exec=" + exec_path);
    args.push_back("Name=" + getDesktopName());
    args.push_back("Icon=" + getDesktopIcon());
    args.push_back("Type=Application");

    QFile desktop_file(QDir::homePath() + "/.local/share/applications/" + desktop_name);
    if(!desktop_file.open(QIODevice::WriteOnly))
    {
        qDebug() << "open fail";
        return false;
    }
    for(int i = 0; i < args.size(); ++ i)
    {
        int ret = desktop_file.write((args[i] + "\n").toUtf8());
        if(ret == -1)
        {
            qDebug() << "ret == 1";
            desktop_file.close();
            return false;
        }    
    }
    desktop_file.close();

    QMessageBox::information(nullptr, "提示", "创建成功", QMessageBox::Ok);
    return true;
}

bool Desktop_Creator::deleteDesktop()
{
    QString desktop_name = getDesktopName() + ".desktop";
    QString desktop_file_path = QDir::homePath() + "/.local/share/applications/" + desktop_name;
    if(!QFile::exists(desktop_file_path))
    {
        QMessageBox::warning(nullptr, "警告", "快捷方式不存在", QMessageBox::Ok);
        return false;
    }
    else
    {
        int ret = QFile::remove(desktop_file_path);
        if(ret == false)
        {
            QMessageBox::warning(nullptr, "警告", "快捷方式删除失败", QMessageBox::Ok);
        }
        else
        {
            QMessageBox::warning(nullptr, "提示", "快捷方式删除成功", QMessageBox::Ok);
        }

        return ret;
    }
}

QString Desktop_Creator::getDesktopName()
{
    QString version_file_path = QCoreApplication::applicationDirPath() + "/.version.txt";
    if(!QFile::exists(version_file_path)) return "";
    QFile file(version_file_path);
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd())
    {
        QString line = file.readLine();
        if(line.contains("Name"))
        {
            QString name = line.mid(5).remove('\n');
            return name;
        }
    }
    return "";
}

QString Desktop_Creator::getDesktopVersion()
{
    QString version_file_path = QCoreApplication::applicationDirPath() + "/.version.txt";
    if(!QFile::exists(version_file_path)) return "";
    QFile file(version_file_path);
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd())
    {
        QString line = file.readLine();
        if(line.contains("Version"))
        {
            QString version = line.mid(8).remove('\n');
            return version;
        }
    }
    return "";
}

QString Desktop_Creator::getDesktopIcon()
{
    QString icon_folder_path = QCoreApplication::applicationDirPath() + "/.icon";
    QDirIterator it(icon_folder_path);
    while(it.hasNext())
    {
        it.next();
        if(it.fileName() == "." || it.fileName() == ".." || it.fileInfo().isDir()) continue;
        return it.filePath();
    }

    return "";
}