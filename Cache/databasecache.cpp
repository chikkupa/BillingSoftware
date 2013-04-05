#include "databasecache.h"

#define FILENAME "Data/database.txt"

QString DatabaseCache::hostname = "";
QString DatabaseCache::username = "";
QString DatabaseCache::password = "";
QString DatabaseCache::database = "";

DatabaseCache::DatabaseCache()
{
    QFile file(FILENAME);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Error opening file: 'database.txt'";
        return;
    }

    QTextStream in(&file);
    in>>hostname;
    in>>username;
    in>>password;
    in>>database;
    file.close();
}

QString DatabaseCache::getHostname()
{
    return hostname;
}

QString DatabaseCache::getUsername()
{
    return username;
}

QString DatabaseCache::getPassword()
{
    return password;
}

QString DatabaseCache::getDatabase()
{
    return database;
}

void DatabaseCache::reload()
{
    QFile file(FILENAME);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Error opening file: 'database.txt'";
        return;
    }

    QTextStream in(&file);
    in>>hostname;
    in>>username;
    in>>password;
    in>>database;
    file.close();
}
