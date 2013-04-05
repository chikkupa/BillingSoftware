#ifndef DATABASECACHE_H
#define DATABASECACHE_H

#include <QtCore>

class DatabaseCache
{
public:
    DatabaseCache();

    static QString hostname;
    static QString username;
    static QString password;
    static QString database;

    static QString getHostname();
    static QString getUsername();
    static QString getPassword();
    static QString getDatabase();
    static void reload();
};

#endif // DATABASECACHE_H
