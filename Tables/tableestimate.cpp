#include "tableestimate.h"
#include "databaseserver.h"
#include "tablecustomers.h"
#include "tablecommodity.h"

TableEstimate::TableEstimate()
{
}

void TableEstimate::addNewEntry(QString estimateNo, QString customerId, QString commodityId, QString commodity, QString tax, QString price, QString quantity, QString discount, QString total, QDate date)
{
    QString purchasePrice = TableCommodity::getPurchasePrice(commodityId);
    QString grossValue = QString::number(price.toFloat() * quantity.toFloat());
    QString taxableValue = QString::number(grossValue.toFloat() - discount.toFloat());
    QString taxAmount = QString::number(taxableValue.toFloat() * tax.toFloat() / 100);
    QString cess = QString::number(taxAmount.toFloat() * 1 /100);

    QString queryString = "insert into Estimate ";
    queryString += "(EstimateNo, CustomerId, CommodityId, Commodity, Tax, PurchasePrice, Price, Quantity, GrossValue, Discount, TaxableValue, TaxAmount, Cess, Total, Time) ";
    queryString +=  " values ";
    queryString += "(" + estimateNo + ",'" + customerId + "','" + commodityId + "','" + commodity;
    queryString += "','" + tax + "','" + purchasePrice + "','" + price + "','" + quantity;
    queryString += "','" + grossValue + "','" + discount + "','" + taxableValue + "','" + taxAmount + "','" +cess;
    queryString +=  "','" + total + "','" + date.toString("yyyy-MM-dd") + "')";

    DatabaseServer *server = new DatabaseServer;
    server->executeQuery(queryString);
    delete server;
}
void TableEstimate::deleteEstimate(QString estimateNo)
{
    QString custId = getCustomerId(estimateNo);
    TableCustomers::deleteCustomerDetails(custId);
    DatabaseServer *server = new DatabaseServer;
    server->executeQuery("delete from Estimate where EstimateNo = " + estimateNo);
    delete server;
}

QStringList TableEstimate::getEstimateDetails(QString estimateNo)
{
    DatabaseServer *server = new DatabaseServer;
    QStringList details = server->getMultiListResult("select CommodityId, Commodity, Tax, Price, Quantity, Discount, TaxableValue, TaxAmount, Total from Estimate where EstimateNo = " + estimateNo);
    delete server;
    return details;
}

QString TableEstimate::getCustomerId(QString estimateNo)
{
    DatabaseServer *server = new DatabaseServer;
    QString id = server->getSingleResult("select CustomerId from Estimate where EstimateNo=" + estimateNo + " limit 1");
    delete server;
    return id;
}

QDate TableEstimate::getDate(QString estimateNo)
{
    DatabaseServer *server = new DatabaseServer;
    QString dt = server->getSingleResult("select Date(Time) from Estimate where EstimateNo=" + estimateNo + " limit 1");
    delete server;
    QDate date = QDate::fromString(dt, "yyyy-MM-dd");
    return date;
}

void TableEstimate::clearAll()
{
    DatabaseServer server;
    server.executeQuery("delete from Estimate");
}

