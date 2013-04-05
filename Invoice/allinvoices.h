#ifndef ALLINVOICES_H
#define ALLINVOICES_H

#include <QWidget>
#include "listtablewidget.h"

class AllInvoices : public QWidget
{
    Q_OBJECT
public:
    explicit AllInvoices(int wid = 500, QWidget *parent = 0);

private:
    int width;

    ListTableWidget *table;
signals:
    void setHeader(QString);
    void setTotal(QString);

public slots:
    void setData();
    void printReport();
};

#endif // ALLINVOICES_H
