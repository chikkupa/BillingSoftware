#include "historydsrwidget.h"
#include <QtGui>
#include "databaseserver.h"
#include "commons.h"
#include <QtWebKit>
#include "printviewdialog.h"

HistoryDSRWidget::HistoryDSRWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *header = new QLabel;
    table = new ListTableWidget;
    QLabel *label1 = new QLabel("Enter Date: ");
    QDateEdit *dateEdit = new QDateEdit;
    dateEdit->setDate(QDate::currentDate());
    QLabel *total = new QLabel;
    QPushButton *print = new QPushButton("Print");
    print->setMaximumWidth(150);
    hlay2->addStretch();
    hlay2->addWidget(label1);
    hlay2->addWidget(dateEdit);
    hlay2->addStretch();
    hlay1->addWidget(print);
    hlay1->addWidget(total);

    mainLayout->addWidget(header);
    mainLayout->addLayout(hlay2);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay1);

    connect(dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setData(QDate)));
    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(print, SIGNAL(clicked()), this, SLOT(printReport()));
}

void HistoryDSRWidget::setData(QDate dateEdit)
{
    QString date;
    setHeader(Commons::getHeaderWithAddress() + "<br><br><center><font size=5><b>History Sales Report</b></font></center>");
    DatabaseServer server;
    date = dateEdit.toString("yyyy-MM-dd");
    historyDate = dateEdit;
    QStringList values = server.getListTableResult(" select  InvoiceNo, TinNo, Dealer, sum(Total) as Total from Invoice where Time like '" + date + "%' group by InvoiceNo;");

    table->setList(values);

    for(int i=0; i<table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width-50)/table->columnCount());
    }
    QString total = server.getSingleResult("select sum(Total) from Invoice where Time like '" + date + "%';");
    setTotal("<font size=4><center><b>Total: <font size=5>" + Commons::getCommaSeperatedValue(total) +"<br>");
}

void HistoryDSRWidget::printReport()
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString filename = "SalesReport.pdf";
    QString content;
    QTextStream out(&content);
    QStringList htmlContent;
    QString allContent;
    int rowCount = 0;
    int maxItems = 25;
    int ind = 0;
    do
    {
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
        out<<"<br><table width='100%' id=tab>";
        out<<"<tr><td id='tabd'>" + Commons::insertNbspInBetween("SlNo", 1) + "</td>";
        for(int i = 0; i < table->columnCount(); i++)
            out<<"<td id='tabd'>" + Commons::insertNbspInBetween(table->getHeader(i), 1) + "</td>";
        out<<"</tr>";
        for(int i = rowCount; i < table->rowCount(); i++)
        {
            out<<"<tr><td id='tabd'>" + Commons::insertNbspInBetween(QString::number(i + 1), 1) + "</td>";
            for(int j = 0; j < table->columnCount(); j++)
                out<<"<td id='tabd'>" + Commons::insertNbspInBetween(table->getItem(i, j), 1) + "</td>";
            out<<"</tr>";
        }
        int tot = table->getSumOfColumn(5) + 0.99;
        rowCount += maxItems;

        if(rowCount > table->rowCount())
        {
            for(int i = table->rowCount() -1 ; i < rowCount; i++)
            {
                out<<"<tr>";
                for(int j = 0; j < table->columnCount() + 1; j++)
                    out<<"<td id=tabd>&nbsp;</td>";
                out<<"</tr>";
            }
            out<<"<td colspan=4 id='tabd'><b><center>" + Commons::insertNbspInBetween("Total: ", 1) + "<center></b></td><td colspan=3 id='tabd'><b>" + Commons::insertNbspInBetween(QString::number(tot), 1) + "</b></td></tr>";
        }
        out<<"</table>";
        if(rowCount > table->rowCount())
            out<<"</body></html>";

        htmlContent.append(out.readAll());
        allContent += htmlContent.at(ind);
        ind++;

    }while(rowCount < table->rowCount());

    PrintViewDialog dialog;

    if(dialog.setwebView(allContent))
    {
        for(int i = 0; i < htmlContent.size(); i++)
            Commons::printHTML(htmlContent.at(i));
    }
    // Html to PDF conversion

    Commons::htmlToPDF(filename, allContent);
    Commons::htmlToPDF("SalesReport/SalesReport" + QDate::currentDate().toString("ddMMyyyy") + ".pdf", allContent);

//    Commons::openFileOnDefaultApplication(filename);

}

