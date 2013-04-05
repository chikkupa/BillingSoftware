#include "tableconfiguration.h"
#include "databaseserver.h"

TableConfiguration::TableConfiguration()
{
}

bool TableConfiguration::getCheckStockStatus()
{
    DatabaseServer server;
    int checkStockStatus = server.getSingleResult("select Value from Details where Field='StockCheck'").toInt();
    if(checkStockStatus)
        return true;
    return false;
}

bool TableConfiguration::getReturnItemStatus()
{
    DatabaseServer server;
    int checkStockStatus = server.getSingleResult("select Value from Configuration where Field='ReturnItem'").toInt();
    if(checkStockStatus)
        return true;
    return false;
}
