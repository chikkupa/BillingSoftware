#ifndef PURCHASEDITEMWIDGET_H
#define PURCHASEDITEMWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QLineEdit;
class QComboBox;
class QDateEdit;

class PurchasedItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PurchasedItemWidget(int wid = 500, QWidget *parent = 0);

private:

private:
    int width;

    QComboBox *searchBy;
    QComboBox *searchType;
    QLineEdit *searchKey;
    ListTableWidget *table;
    QDate itemDate;
    QDateEdit *dateStart;
    QDateEdit *dateEnd;

signals:
    void setHeader(QString);
    void setTotal(QString);

public slots:
    void setData(QDate = QDate::currentDate());
    void setData(QString);
    void printReport();
    void exportToCSV();
    void openAsSpreadSheet();
};

#endif // PURCHASEDITEMWIDGET_H
