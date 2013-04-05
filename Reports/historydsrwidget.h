#ifndef HISTORYDSRWIDGET_H
#define HISTORYDSRWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDateEdit>

class HistoryDSRWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryDSRWidget(int wid = 500, QWidget *parent = 0);

private:
    int width;

    ListTableWidget *table;
    QDate historyDate;

signals:
    void setHeader(QString);
    void setTotal(QString);

public slots:
    void setData(QDate dateEdit = QDate::currentDate());
    void printReport();
};
#endif // HISTORYDSRWIDGET_H
