#include "backup.h"
#include <QFile>
#include "databaseserver.h"

Backup::Backup()
{
}

void Backup::saveBackup(QString filename)
{
    QFile file(filename);

        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug()<<"Error opening file!!";
            return;
        }

        QTextStream out(&file);
        QString backupData;
        DatabaseServer server;

        QStringList tablenames = server.getListResult("show tables");

        for(int index = 0; index < tablenames.size(); index++)
        {
            QString tablename = tablenames.at(index);
            backupData += "Data " + tablename;
            backupData += "\nStart";
            QList<QStringList> table = server.get2DListTableResult("select * from " + tablename);
            for(int i = 1; i < table.size(); i++)
            {
                backupData += "\n('";
                backupData += table.at(i).at(0);
                for(int j = 1; j < table.at(i).size(); j++)
                {
                    backupData += "','" + table.at(i).at(j);
                }
                backupData += "')";
                if(i != table.size() - 1)
                    backupData += ",";
            }
            backupData += "\nEnd\n\n";
        }
        out<<backupData;
        file.close();
}
