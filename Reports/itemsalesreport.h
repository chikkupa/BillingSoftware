#ifndef ITEMSALESREPORT_H
#define ITEMSALESREPORT_H

#include <QDialog>
#include "listtablewidget.h"
#include <QDateEdit>

class QComboBox;

class ItemSalesReport : public QDialog
{
    Q_OBJECT
public:
    explicit ItemSalesReport(QWidget *parent = 0);
    
signals:

private:
    int width;

    QDateEdit *dateStart;
    QDateEdit *dateEnd;
    QComboBox *commodityId;
    QComboBox *commodityName;
    ListTableWidget *table;
    QDate itemDate;

signals:
    void setHeader(QString);
    void setTotal(QString);

public slots:
    void getItemSales();
    void setData(QDate);
    void printReport();
    void checkCode();
    void addItem();
    void removeItem();
    void getSummary();
    
};

#endif // ITEMSALESREPORT_H
