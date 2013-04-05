#include "tableinvoice.h"
#include "databaseserver.h"
#include "tablecustomers.h"
#include "tablecommodity.h"

TableInvoice::TableInvoice()
{
}

void TableInvoice::addNewEntry(QString invoiceNo, QString customerId, QString commodityId, QString commodity, QString tax, QString price, QString quantity, QString discount, QString total, QDate date)
{
    QString purchasePrice = TableCommodity::getPurchasePrice(commodityId);
    QString grossValue = QString::number(price.toFloat() * quantity.toFloat());
    QString taxableValue = QString::number(grossValue.toFloat() - discount.toFloat());
    QString taxAmount = QString::number(taxableValue.toFloat() * tax.toFloat() / 100);
    QString cess = QString::number(taxAmount.toFloat() * 1 /100);

    QString queryString = "insert into Invoice ";
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

void TableInvoice::deleteInvoice(QString invoiceNo)
{
    QString custId = getCustomerId(invoiceNo);
    TableCustomers::deleteCustomerDetails(custId);
    DatabaseServer *server = new DatabaseServer;
    server->executeQuery("delete from Invoice where InvoiceNo = " + invoiceNo);
    delete server;
}

QStringList TableInvoice::getInvoiceDetails(QString invoiceNo)
{
    DatabaseServer *server = new DatabaseServer;
    QStringList details = server->getMultiListResult("select CommodityId, Commodity, Tax, Price, Quantity, Discount, TaxableValue, TaxAmount, Total from Invoice where InvoiceNo = " + invoiceNo);
    delete server;
    return details;
}

QString TableInvoice::getCustomerId(QString invoiceNo)
{
    DatabaseServer *server = new DatabaseServer;
    QString id = server->getSingleResult("select CustomerId from Invoice where InvoiceNo=" + invoiceNo + " limit 1");
    delete server;
    return id;
}

QDate TableInvoice::getDate(QString invoiceNo)
{
    DatabaseServer *server = new DatabaseServer;
    QString dt = server->getSingleResult("select Date(Time) from Invoice where InvoiceNo=" + invoiceNo + " limit 1");
    delete server;
    QDate date = QDate::fromString(dt, "yyyy-MM-dd");
    return date;
}

void TableInvoice::invoiceToEstimate(QString includeCond, QDate dateStart, QDate dateEnd)
{
    DatabaseServer server;
    QString query = "select SlNo, InvoiceNo, CustomerId, CommodityId, Commodity, Tax, PurchasePrice, Price, Quantity, ";
    query += "GrossValue, Discount, TaxableValue, TaxAmount, Cess, Total, Time from Invoice ";
    query += "where CommodityId like '" + includeCond + "%' and Time >= '";
    query += dateStart.toString("yyyy-MM-dd") + "' and Time <= '" + dateEnd.toString("yyyy-MM-dd") + "'";
    QList<QStringList> invoices = server.get2DListTableResult(query);

    QString currentInvoiceNo = "0";
    QString estimateNo = server.getSingleResult("select Value from Details where Field='Estimate'");

    for(int i = 1; i < invoices.size(); i++)
    {
        QStringList item = invoices.at(i);

        if(item.at(1) != currentInvoiceNo)
        {
            // Set Next Invoice No
            QString inNo = server.getSingleResult("select Value from Details where Field='Estimate'");

            do
            {
                QString inCurr = server.getSingleResult("select distinct EstimateNo from Estimate where EstimateNo='" + inNo + "';");
                if( inNo == inCurr)
                    inNo = QString::number(inNo.toInt() + 1);
                else
                {
                    server.executeQuery("update Details set Value ='" + inNo + "' where Field='Estimate'");
                    break;
                }
            }while(true);
            // Get next Invoice No
            estimateNo = server.getSingleResult("select Value from Details where Field='Estimate'");
            currentInvoiceNo = item.at(1);
        }
        query = "insert into Estimate (EstimateNo, CustomerId, CommodityId, Commodity, Tax, PurchasePrice, Price, Quantity, ";
        query += "GrossValue, Discount, TaxableValue, TaxAmount, Cess, Total, Time)";
        query += " values ";
        query += "('" + estimateNo + "','" + item.at(2) + "','" + item.at(3) + "','" + item.at(4) + "','" + item.at(5);
        query += "','" + item.at(6) + "','" + item.at(7) + "','" + item.at(8) + "','" + item.at(9) + "','" + item.at(10);
        query += "','" + item.at(11) + "','" + item.at(12) + "','" + item.at(13) + "','" + item.at(14) + "','" + item.at(15) + "')";
        server.executeQuery(query);
        query = "delete from Invoice where SlNo=" + item.at(0);
        server.executeQuery(query);
    }
}

QStringList TableInvoice::getDistinctTaxInBetweenDates(QDate date1, QDate date2)
{
    DatabaseServer *server = new DatabaseServer;
    QStringList tax = server->getListResult("select distinct Tax from Invoice where Time >= '" + date1.toString("yyyy-MM-dd") + "' and Time <= '" + date2.toString("yyyy-MM-dd") + "' order by Tax");
    delete server;
    return tax;
}
