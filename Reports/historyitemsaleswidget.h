#ifndef HISTORYITEMSALESWIDGET_H
#define HISTORYITEMSALESWIDGET_H

#include <QWidget>
#include "listtablewidget.h"

#include <QDateEdit>

class HistoryItemSalesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryItemSalesWidget(int wid =500, QWidget *parent = 0);


private:
    int width;

    QDateEdit *dateStart;
    QDateEdit *dateEnd;
    ListTableWidget *table;
    QDate itemDate;

signals:
    void setHeader(QString);
    void setTotal(QString);

public slots:
    void setData(QDate);
    void printReport();
    void exportToCSV();
    void openAsSpreadSheet();
};

#endif // HISTORYITEMSALESWIDGET_H
