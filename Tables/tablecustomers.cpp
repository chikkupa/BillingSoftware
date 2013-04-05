#include "tablecustomers.h"
#include "databaseserver.h"

TableCustomers::TableCustomers()
{
}

int TableCustomers::addNewCustomer(QString name, QString address, QString telephone, QString mobile, QString email)
{
    DatabaseServer *server = new DatabaseServer;
    QString query = "insert into Customers (Name, Address, Telephone, Mobile, Email)";
    query += "values ('" + name + "', '" + address + "', '";
    query += telephone + "', '" + mobile + "', '" + email + "')";
    server->executeQuery(query);
    delete server;
    return getLastSlNo();
}

QStringList TableCustomers::getCustomerDetails(QString customerId)
{
    DatabaseServer server;
    QStringList details;
    details = server.getRowResult("select Name, Address, Telephone, Mobile, Email from Customers where SlNo=" + customerId);
    return details;
}

int TableCustomers::getLastSlNo()
{
    DatabaseServer server;
    QString lastSlNo = server.getSingleResult("select max(SlNo) from Customers");
    return lastSlNo.toInt();
}

void TableCustomers::deleteCustomerDetails(QString customerId)
{
    DatabaseServer *server = new DatabaseServer;
    server->executeQuery("delete from Customers where SlNo=" + customerId);
    delete server;
}
