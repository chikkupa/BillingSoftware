#ifndef HISTORYINVOICEWIDGET_H
#define HISTORYINVOICEWIDGET_H

#include <QWidget>
#include "listtablewidget.h"

class QLineEdit;

class HistoryInvoiceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryInvoiceWidget(int wid = 500, QWidget *parent = 0);

private:
    int width;
    QStringList dealerId;
    QLineEdit *invoiceNo;
    ListTableWidget *table;
    QString invoiceDate;

signals:
    void setHeader(QString);
    void setDetails(QString);
    void setTotal(QString);

public slots:
    void setData();
    void printInvoice();

};

#endif // HISTORYINVOICEWIDGET_H
