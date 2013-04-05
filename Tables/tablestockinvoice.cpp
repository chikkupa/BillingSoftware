#include "tablestockinvoice.h"
#include "databaseserver.h"
#include "tablecustomers.h"
#include "tablecommodity.h"

TableStockInvoice::TableStockInvoice()
{
}

void TableStockInvoice::addNewEntry(QString invoiceNo, QString customerId, QString commodityId, QString commodity, QString tax, QString price, QString quantity, QString total, QDate date)
{
    QString purchasePrice = TableCommodity::getPurchasePrice(commodityId);
    QString grossValue = QString::number(price.toFloat() * quantity.toFloat());
    QString discount = "0";
    QString taxableValue = QString::number(grossValue.toFloat() - discount.toFloat());
    QString taxAmount = QString::number(taxableValue.toFloat() * tax.toFloat() / 100);
    QString cess = QString::number(taxAmount.toFloat() * 1 /100);

    QString queryString = "insert into StockInvoice ";
    queryString += "(InvoiceNo, CustomerId, CommodityId, Commodity, Tax, PurchasePrice, Price, Quantity, GrossValue, Discount, TaxableValue, TaxAmount, Cess, Total, Time) ";
    queryString +=  " values ";
    queryString += "(" + invoiceNo + ",'" + customerId + "','" + commodityId + "','" + commodity;
    queryString += "','" + tax + "','" + purchasePrice + "','" + price + "','" + quantity;
    queryString += "','" + grossValue + "','" + discount + "','" + taxableValue + "','" + taxAmount + "','" +cess;
    queryString +=  "','" + total + "','" + date.toString("yyyy-MM-dd") + "')";

    DatabaseServer *server = new DatabaseServer;
    server->executeQuery(queryString);
    delete server;
}

void TableStockInvoice::deleteInvoice(QString invoiceNo)
{
    QString custId = getCustomerId(invoiceNo);
    TableCustomers::deleteCustomerDetails(custId);
    DatabaseServer *server = new DatabaseServer;
    server->executeQuery("delete from StockInvoice where InvoiceNo = " + invoiceNo);
    delete server;
}

QString TableStockInvoice::getCustomerId(QString invoiceNo)
{
    DatabaseServer *server = new DatabaseServer;
    QString id = server->getSingleResult("select CustomerId from StockInvoice where InvoiceNo=" + invoiceNo + " limit 1");
    delete server;
    return id;
}

QStringList TableStockInvoice::getStockInvoiceDetails(QString invoiceNo)
{
    DatabaseServer *server = new DatabaseServer;
    QStringList details = server->getMultiListResult("select CommodityId, Commodity, Tax, PurchasePrice, Quantity, TaxableValue, TaxAmount, Total from StockInvoice where InvoiceNo = " + invoiceNo);
    delete server;
    return details;
}

QDate TableStockInvoice::getDate(QString invoiceNo)
{
    DatabaseServer *server = new DatabaseServer;
    QString dt = server->getSingleResult("select Date(Time) from StockInvoice where InvoiceNo=" + invoiceNo + " limit 1");
    delete server;
    QDate date = QDate::fromString(dt, "yyyy-MM-dd");
    return date;
}

QStringList TableStockInvoice::getDistinctTaxInBetweenDates(QDate date1, QDate date2)
{
    DatabaseServer *server = new DatabaseServer;
    QStringList tax = server->getListResult("select distinct Tax from Invoice where Time >= '" + date1.toString("yyyy-MM-dd") + "' and Time <= '" + date2.toString("yyyy-MM-dd") + "' order by Tax");
    delete server;
    return tax;
}
