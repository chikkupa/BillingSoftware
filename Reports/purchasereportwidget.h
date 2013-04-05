#ifndef PURCHASEREPORTWIDGET_H
#define PURCHASEREPORTWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QRadioButton;

class PurchaseReportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PurchaseReportWidget(int wid = 500, QWidget *parent = 0);

private:
    int width;
    QDate date1;
    QDate date2;
    QRadioButton *normalView;
    QRadioButton *taxView;


    ListTableWidget *table;
signals:
    void setHeader(QString);
    void setTotal(QString);

public slots:
    void setDate1(QDate);
    void setDate2(QDate);
    void setData();
    void printReport();
    void exportToCSV();
    void openAsSpreadSheet();
};

#endif // PURCHASEREPORTWIDGET_H
