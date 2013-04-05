#ifndef TABLESTOCKINVOICE_H
#define TABLESTOCKINVOICE_H

#include <QtCore>

class TableStockInvoice
{
public:
    TableStockInvoice();
    static void addNewEntry(QString invoiceNo, QString customerId, QString commodityId, QString commodity, QString tax, QString price, QString quantity, QString total, QDate date);
    static void deleteInvoice(QString invoiceNo);
    static QString getCustomerId(QString invoiceNo);
    static QStringList getStockInvoiceDetails(QString invoiceNo);
    static QDate getDate(QString invoiceNo);
    static QStringList getDistinctTaxInBetweenDates(QDate date1, QDate date2);
};

#endif // TABLESTOCKINVOICE_H
