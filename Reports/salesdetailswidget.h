#ifndef SALESDETAILSWIDGET_H
#define SALESDETAILSWIDGET_H

#include <QWidget>
#include "listtablewidget.h"

class SalesDetailsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SalesDetailsWidget(int wid =500, QWidget *parent = 0);

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

#endif // SALESDETAILSWIDGET_H
