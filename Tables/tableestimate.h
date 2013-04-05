#ifndef TABLEESTIMATE_H
#define TABLEESTIMATE_H

#include <QtCore>

class TableEstimate
{
public:
    TableEstimate();
    static void addNewEntry(QString estimateNo, QString customerId, QString commodityId, QString commodity, QString tax, QString price, QString quantity, QString discount, QString total, QDate date);
    static void deleteEstimate(QString estimateNo);
    static QStringList getEstimateDetails(QString estimateNo);
    static QString getCustomerId(QString estimateNo);
    static QDate getDate(QString estimateNo);
    static void clearAll();
};

#endif // TABLEESTIMATE_H
