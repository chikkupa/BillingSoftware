#include "tablecommodity.h"
#include "databaseserver.h"

TableCommodity::TableCommodity()
{

}

QStringList TableCommodity::getCommodityIds()
{
    DatabaseServer server;
    QStringList ids = server.getListResult("select Id from Commodity order by Name");
    return ids;
}

QStringList TableCommodity::getCommodityNames()
{
    DatabaseServer server;
    QStringList ids = server.getListResult("select Name from Commodity order by Name");
    return ids;
}

QStringList TableCommodity::getAllCommodities()
{
    DatabaseServer server;
    QStringList commodities = server.getMultiListResult("select  Id, Name, Tax, PurchasePrice, Price, Cess, Quantity from  Commodity order by Name");
    return commodities;
}

QStringList TableCommodity::getCommodityTable(QString searchBy, int searchType, QString searchKey)
{
    QString searchQuery;
    if(searchKey != "")
    {
        QString key;
        switch(searchType)
        {
        case 1: key = searchKey + "%"; break;
        case 2: key = "%" + searchKey; break;
        case 3: key = searchKey; break;
        case 4: key = "%" + searchKey + "%"; break;
        }

        searchQuery += " " + searchBy + " like '" + key + "'";
    }

    QString query = "select Id, Name, Tax, PurchasePrice, Price, Cess, Quantity, PurchasePrice * Quantity as Total, DATE_FORMAT(LastUpdate, '%d/%m/%Y') as LastUpdate from Commodity";
    if(searchQuery != "")
    {
        query += " where " + searchQuery;
    }
    query += " order by Name";
    DatabaseServer server;
    QStringList table = server.getListTableResult(query);
    return table;
}

void TableCommodity::addNewItem(QString id, QString name, QString tax, QString purchasePrice, QString price, QString cess, QString quantity)
{
    DatabaseServer server;
    tax = QString::number(tax.toFloat());
    cess = QString::number(cess.toInt());
    purchasePrice = QString::number(purchasePrice.toFloat());
    quantity = QString::number(quantity.toFloat());
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    server.executeQuery("insert into Commodity (Id, Name, Tax, PurchasePrice, Price, Cess, Quantity, LastUpdate) values ('" + id + "', '" + name + "', " + tax + ", '" + purchasePrice + "', '" + price + "', '" + cess + "', '" + quantity + "', '" + date + "')");
}

void TableCommodity::removeItem(QString id)
{
    DatabaseServer server;
    server.executeQuery("delete from Commodity where Id='" + id + "'");
}

void TableCommodity::editItem(QString id, QString name, QString tax, QString purchasePrice, QString price, QString cess, QString quantity, QString oldId)
{
    tax = QString::number(tax.toFloat());
    cess = QString::number(cess.toInt());
    purchasePrice = QString::number(purchasePrice.toFloat());
    quantity = QString::number(quantity.toFloat());
    DatabaseServer server;
    server.executeQuery("update Commodity set Id = '" + id + "', Name = '" + name + "', Tax = '" + tax + "', PurchasePrice = '" + purchasePrice + "', Price = '" + price + "', Cess = '" + cess + "', Quantity = '" + quantity + "', LastUpdate = '" + QDate::currentDate().toString("yyyy-MM-dd") + "' where Id = '" + oldId + "'");
}

void TableCommodity::updateItem(QString id, QString price, QString addedQantity)
{
    DatabaseServer server;
    server.executeQuery("update Commodity set Price = '" + price + "', Quantity = Quantity + " + addedQantity + " where Id = '" + id + "'");
}

QStringList TableCommodity::getUpdateTable()
{
    DatabaseServer server;
    QStringList table = server.getListTableResult("select Id, Name, Quantity, Price, 0 as 'Update Quantity' from Commodity");
    return table;
}

void TableCommodity::bulkUpdate(QList<QStringList> tableDetails)
{
    DatabaseServer server;
    for(int i = 0; i < tableDetails.size(); i++)
    {
        QStringList row = tableDetails.at(i);
        QString id = row.at(0);
        QString price = row.at(3);
        QString addedQuantity = row.at(4);
        server.executeQuery("update Commodity set Price = '" + price + "', Quantity = Quantity + " + addedQuantity + " where Id = '" + id + "'");
    }
}

QString TableCommodity::getPurchasePrice(QString commodityId)
{
    DatabaseServer server;
    QString purchasePrice = server.getSingleResult("select PurchasePrice from Commodity where Id='" + commodityId + "'");
    return purchasePrice;
}

QStringList TableCommodity::getItemSalesDetails(QString commodityId, QDate startDate, QDate endDate)
{
    QString query = "select A.CommodityId, A.Commodity, B.PurchasePrice as 'Purchase Price', ";
    query += "A.Price as 'Sales Price', sum(A.Quantity) as Quantity, A.PurchasePrice * sum(A.Quantity) ";
    query += "as 'Purchase Total', sum(A.GrossValue - Discount) as 'Sales Total', ";
    query += "sum(A.Total) as 'Total Amount', sum(A.GrossValue - Discount) - A.PurchasePrice * sum(A.Quantity) ";
    query += "as Profit from Invoice A left join Commodity B on A.CommodityId=B.Id where ";
    query += "Time >= '" + startDate.toString("yyyy-MM-dd") + "' and Time <= '" + endDate.toString("yyyy-MM-dd") + "' and CommodityId='" + commodityId + "' ";
    query += "group by Commodity";
    query += " union ";
    query += "select Id, Name, PurchasePrice, Price, 0, 0, 0, 0, 0 ";
    query += "from Commodity where Id='" + commodityId + "'";
    DatabaseServer server;
    QStringList result = server.getMultiListResult(query);
    return result;
}
