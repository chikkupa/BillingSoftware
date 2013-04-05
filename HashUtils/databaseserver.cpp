#include "databaseserver.h"

#define DB "Billing"
#define HOST "127.0.0.1"
#define USER "root"
#define PASSWORD "123"
#define DATABASE "QMYSQL"

DatabaseServer::DatabaseServer()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DATABASE);
    db.setHostName(HOST);
    db.setDatabaseName(DB);
    db.setUserName(USER);
    db.setPassword(PASSWORD);
    if (!db.open())
    {
        qDebug() << db.lastError();
    }
}

void DatabaseServer::executeQuery(QString queryString)
{
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();
    qDebug() << query.lastError();
}

QSqlQueryModel* DatabaseServer::getQueryModel(QString query)
{
    QSqlQueryModel *queryResultModel= new QSqlQueryModel;
    queryResultModel->setQuery(query);
    return queryResultModel;
}

QString DatabaseServer::getSingleResult(QString queryString)
{
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();
    QSqlRecord record =  query.record();
    QString value;
    if(query.next())
        value = query.value(0).toString();
    return value;
}

QStringList DatabaseServer::getRowResult(QString queryString)
{
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();
    QStringList values;
    query.next();
    if(query.isValid())
    {
        for(int i=0; i< query.record().count(); i++)
        {
            values.append(query.value(i).toString());
        }
    }
    return values;
}

QStringList DatabaseServer::getListResult(QString queryString)
{
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();
    QStringList values;
    while(query.next())
    {
        values.append(query.value(0).toString());
    }
    return values;
}

QStringList DatabaseServer::getMultiListResult(QString queryString)
{
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();
    QStringList values;
    while(query.next())
    {
        QString value;
        value += query.value(0).toString();
        for(int i=1; i< query.record().count(); i++)
            value += "\n" + query.value(i).toString();
        values.append(value);
    }
    return values;
}

QStringList DatabaseServer::getListTableResult(QString queryString)
{
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();
    QStringList values;

    QString value;
    value += query.record().fieldName(0);
    for(int i=1; i< query.record().count(); i++)
        value += "\n" + query.record().fieldName(i);
    values.append(value);

    while(query.next())
    {
        QString value;
        value += query.value(0).toString();
        for(int i=1; i< query.record().count(); i++)
            value += "\n" + query.value(i).toString();
        values.append(value);
    }
    return values;
}

QList<QStringList> DatabaseServer::get2DListTableResult(QString queryString)
{
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();
    QList<QStringList> values;
    QStringList value;
    for(int i=0; i< query.record().count(); i++)
        value.append(query.record().fieldName(i));
    values.append(value);

    while(query.next())
    {
        QStringList value;
        for(int i = 0; i < query.record().count(); i++)
            value.append(query.value(i).toString());
        values.append(value);
    }
    return values;
}

DatabaseServer::~DatabaseServer()
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
}
