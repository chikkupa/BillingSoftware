#ifndef TODAYSITEMSALESWIDGET_H
#define TODAYSITEMSALESWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QLineEdit;
class QComboBox;
class QDateEdit;

class TodaysItemSalesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TodaysItemSalesWidget(int wid = 500, QWidget *parent = 0);

private:

private:
    int width;

    QComboBox *searchBy;
    QComboBox *searchType;
    QLineEdit *searchKey;
    ListTableWidget *table;
    QDate itemDate;
    QDateEdit *dateEdit;

signals:
    void setHeader(QString);
    void setTotal(QString);

public slots:
    void setData(QDate = QDate::currentDate());
    void setData(QString);
    void printReport();
    void invoiceToEstimate();
    void exportToCSV();
    void openAsSpreadSheet();
};
#endif // TODAYSITEMSALESWIDGET_H
