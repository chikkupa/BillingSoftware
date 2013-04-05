#ifndef TABLECUSTOMERS_H
#define TABLECUSTOMERS_H

#include <QtCore>

class TableCustomers
{
public:
    TableCustomers();
    static int addNewCustomer(QString name, QString address, QString telephone, QString mobile, QString email);
    static QStringList getCustomerDetails(QString customerId);
    static int getLastSlNo();
    static void deleteCustomerDetails(QString customerId);
};

#endif // TABLECUSTOMERS_H
