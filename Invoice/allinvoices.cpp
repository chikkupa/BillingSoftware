#include "allinvoices.h"
#include <QtGui>
#include "databaseserver.h"
#include "commons.h"
#include <QtWebKit>

AllInvoices::AllInvoices(int wid, QWidget *parent) :
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

void AllInvoices::setData()
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    setHeader(Commons::getHeaderWithAddress() + "<br><br><center><font size=5><b>All Invoices<br>Date: " + date + "</b></font></center>");
    DatabaseServer server;
    date = QDate::currentDate().toString("yyyy-MM-dd");
    QStringList values = server.getListTableResult("select  InvoiceNo, TinNo, Dealer, Tax, Cess, sum(Total) as Total from Invoice group by InvoiceNo;");

    table->setList(values);

    for(int i=0; i<table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width-50)/table->columnCount());
    }
}

void AllInvoices::printReport()
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString filename = "SalesReport.pdf";
    QString content;
    QTextStream out(&content);
    out<<"<html>\n<body>";
    out<<Commons::getHeaderWithAddress();
    out<<"<br><br><center><b> All Invoices</b></center><br>";
    out<<"<br><table border='1px' width='100%'>";
    out<<"<tr><td>SlNo</td>";
    for(int i = 0; i < table->columnCount(); i++)
        out<<"<td>" + table->getHeader(i) + "</td>";
    out<<"</tr>";
    for(int i = 0; i < table->rowCount(); i++)
    {
        out<<"<tr><td>" + QString::number(i + 1) + "</td>";
        for(int j = 0; j < table->columnCount(); j++)
            out<<"<td>" + table->getItem(i, j) + "</td>";
        out<<"</tr>";
    }
    int tot = table->getSumOfColumn(5) + 0.99;
    out<<"<td colspan=4><b><center>Total: <center></b></td><td colspan=3><b><fonnt size=5>" + QString::number(tot) + "</font></b></td></tr>";
    out<<"</table>";

    // Html to PDF conversion
    QWebView *webView = new QWebView(this);
    webView->setHtml(out.readAll());
    QPrinter *printer = new QPrinter;
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName(filename);
    printer->setPaperSize(QPrinter::A4);
    webView->print(printer);
}
