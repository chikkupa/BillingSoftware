#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include <QtSql>

class QSqlDatabase;

class DatabaseServer
{
    public:
        DatabaseServer();
        QSqlDatabase getDB();
        void executeQuery(QString);
        QSqlQueryModel* getQueryModel(QString);
        QString getSingleResult(QString);
        QStringList getRowResult(QString);
        QStringList getListResult(QString);
        QStringList getMultiListResult(QString);
        QStringList getListTableResult(QString);
        QList<QStringList> get2DListTableResult(QString queryString);
        ~DatabaseServer();
};

#endif // DATABASESERVER_H
