#include "adminhomewidget.h"
#include "databaseserver.h"
#include "commons.h"
#include <QtGui>
#include <QtSql>

AdminHomeWidget::AdminHomeWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *head = new QLabel(Commons::getHeaderWithAddress());
    QLabel *total = new QLabel;

    stock = new ListTableWidget;

    mainLayout->addWidget(head);
    mainLayout->addWidget(total);
    mainLayout->addWidget(stock);

    connect( this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
}

void AdminHomeWidget::setData()
{
    DatabaseServer server;
    QStringList values = server.getListTableResult("select Id,Name,PurchasePrice, Price,Quantity,PurchasePrice * Quantity as Total, DATE_FORMAT(LastUpdate, '%d/%m/%Y') as LastUpdate from Commodity;");

    stock->setList(values);

    for(int i=0; i<stock->columnCount(); i++)
    {
        stock->setColumnWidth(i,(width-50)/stock->columnCount());
    }
    QString total = server.getSingleResult("select sum(PurchasePrice * Quantity) from Commodity;");
    setTotal("<font size=4><center><b>Present Stock Value: <font size=5>" + Commons::getCommaSeperatedValue(total) +"<br>");
}
