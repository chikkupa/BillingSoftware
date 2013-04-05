#ifndef TABLEINVOICE_H
#define TABLEINVOICE_H

#include <QtGui>

class TableInvoice
{
public:
    TableInvoice();
    static void addNewEntry(QString invoiceNo, QString customerId, QString commodityId, QString commodity, QString tax, QString price, QString quantity, QString discount, QString total, QDate date);
    static void deleteInvoice(QString invoiceNo);
    static QStringList getInvoiceDetails(QString invoiceNo);
    static QString getCustomerId(QString invoiceNo);
    static QDate getDate(QString invoiceNo);
    static void invoiceToEstimate(QString includeCond, QDate dateStart, QDate dateEnd);
    static QStringList getDistinctTaxInBetweenDates(QDate date1, QDate date2);
};

#endif // TABLEINVOICE_H
