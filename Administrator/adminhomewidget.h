#ifndef ADMINHOMEWIDGET_H
#define ADMINHOMEWIDGET_H

#include <QWidget>
#include "listtablewidget.h"

class QTableView;

class AdminHomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdminHomeWidget(int wid=500, QWidget *parent = 0);

private:
    int width;

    ListTableWidget *stock;
signals:
    void setTotal(QString);

public slots:
    void setData();

};

#endif // ADMINHOMEWIDGET_H
