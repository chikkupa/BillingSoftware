#include "salesdetailswidget.h"
#include <QtGui>
#include <QtWebKit>
#include "commons.h"
#include "databaseserver.h"
#include "printviewdialog.h"

SalesDetailsWidget::SalesDetailsWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *header = new QLabel;
    table = new ListTableWidget;
    QLabel *total = new QLabel;
    QPushButton *print = new QPushButton("Print");
    print->setMaximumWidth(150);
    hlay1->addWidget(print);
    hlay1->addWidget(total);

    mainLayout->addWidget(header);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay1);

    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(print, SIGNAL(clicked()), this, SLOT(printReport()));
}

void SalesDetailsWidget::setData()
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    setHeader(Commons::getHeaderWithAddress() + "<br><br><center><b>Today's Sales Details<br>Date: " + date + "</b></center>");
    DatabaseServer server;
    date = QDate::currentDate().toString("yyyy-MM-dd");
    QStringList values = server.getListTableResult("select Dealer,sum(Total) as Total from Invoice where Time like '" + date + "%'  group by Dealer;");

    table->setList(values);

    for(int i=0; i<table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width-50)/table->columnCount());
    }
    QString total = server.getSingleResult("select sum(Total) from Invoice where Time like '" + date + "%';");
    setTotal("<font size=4><center><b>Total: <font size=5>" + Commons::getCommaSeperatedValue(total) +"<br>");
}

void SalesDetailsWidget::printReport()
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString filename = "ItemSales.pdf";
    QString content;
    QTextStream out(&content);
    out<<"<html>\n<style type='text/css'>";
//        out<<"#tab { border: 1px solid #000; border-width: 1px 0 0 1px; font-weight:bold; }";
//        out<<"#tabd{ border: 1px solid #000; border-width: 0 1px 1px 0; }body {background: white;}";
    out<<"#menu { display: none;} #wrapper, #content { width: auto; margin: 0 5%; padding: 0; border: 0; float: none; color: black; }";
    out<<"body { width: auto; margin: 0 5%; padding: 0; border: 0; float: none; color: black; }</style> <body>";
    out<<"</style> <body>";
    out<<"<center><b><font size=2>" + Commons::insertNbspInBetween(Commons::getShopName().toUpper(), 1) + "</b>";
    out<<"<br>" + Commons::insertNbspInBetween(Commons::getShopAddress(),1) + "</center>";
    out<<Commons::insertNbspInBetween("Tin No: ", 1) + Commons::insertNbspInBetween(Commons::getTinNo(),1);
    out<<Commons::getNbsps(80) + Commons::insertNbspInBetween("Mobile No: ", 1) + Commons::insertNbspInBetween(Commons::getMobileNo(),1);
    out<<"<br><br><center><b>" + Commons::insertNbspInBetween("Sales Report: ", 1) + Commons::insertNbspInBetween(date, 1) + "</b></center><br>";
    out<<"<br><table width='100%'>";
    out<<"<tr><td>" + Commons::insertNbspInBetween("SlNo", 1) + "</td>";
    for(int i = 0; i < table->columnCount(); i++)
        out<<"<td>" + Commons::insertNbspInBetween(table->getHeader(i), 1) + "</td>";
    out<<"</tr>";
    for(int i = 0; i < table->rowCount(); i++)
    {
        out<<"<tr><td>" + Commons::insertNbspInBetween(QString::number(i + 1),1) + "</td>";
        for(int j = 0; j < table->columnCount(); j++)
            out<<"<td>" + Commons::insertNbspInBetween(table->getItem(i, j), 1) + "</td>";
        out<<"</tr>";
    }
    int tot = table->getSumOfColumn(1) + 0.99;
    out<<"<td colspan=2><b><center>" + Commons::insertNbspInBetween("Total: ", 1) + "<center></b></td><td colspan=2><b><fonnt size=5>" + Commons::insertNbspInBetween(QString::number(tot), 1) + "</font></b></td></tr>";
    out<<"</table>";

    // Html to PDF conversion
    QString htmlContent = out.readAll();

    PrintViewDialog dialog;

    if(dialog.setwebView(htmlContent))
    {
        Commons::printHTML(htmlContent);
    }
}

