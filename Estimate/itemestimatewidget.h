#ifndef ITEMESTIMATEWIDGET_H
#define ITEMESTIMATEWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QVBoxLayout;
class QLineEdit;
class QComboBox;
class QDateEdit;

class ItemEstimateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ItemEstimateWidget(int wid = 500, QWidget *parent = 0);

private:

private:
    int width;

    QVBoxLayout *mainLayout;

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
    void setData();
    void setTable(QDate = QDate::currentDate());
    void setTable(QString);
    void printReport();
};

#endif // ITEMESTIMATEWIDGET_H
