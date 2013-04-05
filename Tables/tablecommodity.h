#ifndef TABLECOMMODITY_H
#define TABLECOMMODITY_H

#include <QtCore>

class TableCommodity
{
public:
    TableCommodity();

    static QStringList getCommodityIds();
    static QStringList getCommodityNames();
    static QStringList getAllCommodities();
    static QStringList getCommodityTable(QString searchBy, int searchType, QString searchKey);
    static void addNewItem(QString id, QString name, QString tax, QString purchasePrice, QString price, QString cess, QString quantity);
    static void removeItem(QString item);
    static void editItem(QString id, QString name, QString tax, QString purchasePrice, QString price, QString cess, QString quantity, QString oldId);
    static void updateItem(QString id, QString price, QString  addedQantity);
    static QStringList getUpdateTable();
    static void bulkUpdate(QList<QStringList> tableDetails);
    static QString getPurchasePrice(QString commodityId);
    static QStringList getItemSalesDetails(QString commodityId, QDate startDate, QDate endDate);
};

#endif // TABLECOMMODITY_H
