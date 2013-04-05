#include "todaysitemsaleswidget.h"
#include <QtGui>
#include <QtWebKit>
#include "commons.h"
#include "databaseserver.h"
#include "printviewdialog.h"
#include "printmodule.h"
#include "tableinvoice.h"

TodaysItemSalesWidget::TodaysItemSalesWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *header = new QLabel;

    dateEdit = new QDateEdit();
    dateEdit->setDate(QDate::currentDate());
    searchBy = new QComboBox;
    QStringList list;
    list<<"CommodityId"<<"Commodity";
    searchBy->addItems(list);
    searchType = new QComboBox;
    list.clear();
    list<<"Starting With"<<"Ending With"<<"Equals"<<"Contains";
    searchType->addItems(list);
    searchKey = new QLineEdit;
    table = new ListTableWidget;
    QLabel *label1 = new QLabel("Enter Date: ");
    QLabel *label2 = new QLabel("Search By ");
    QLabel *label3 = new QLabel(" Search Key ");
    QLabel *total = new QLabel;
    QPushButton *print = new QPushButton("Print");
    QPushButton *toEstimate = new QPushButton("To Estimate");
    QPushButton *exportToCSVButton = new QPushButton("Export to CSV");
    QPushButton *openAsSpreadsheetButton = new QPushButton("Open as Spreadsheet");
    print->setMaximumWidth(150);
    exportToCSVButton->setMaximumWidth(150);
    openAsSpreadsheetButton->setMaximumWidth(150);
    toEstimate->setShortcut(QKeySequence("Ctrl+Y"));
    toEstimate->setMaximumWidth(0);

    hlay2->addWidget(label2);
    hlay2->addWidget(searchBy);
    hlay2->addWidget(searchType);
    hlay2->addWidget(label3);
    hlay2->addWidget(searchKey);
    hlay2->addStretch();
    hlay2->addWidget(label1);
    hlay2->addWidget(dateEdit);
    hlay2->addStretch();
    hlay2->addWidget(toEstimate);
    hlay1->addWidget(print);
    hlay1->addWidget(exportToCSVButton);
    hlay1->addWidget(openAsSpreadsheetButton);
    hlay1->addWidget(total);

    mainLayout->addWidget(header);
    mainLayout->addLayout(hlay2);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay1);

    connect(dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setData(QDate)));
    connect(searchKey, SIGNAL(textChanged(QString)), this, SLOT(setData(QString)));
    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(print, SIGNAL(clicked()), this, SLOT(printReport()));
    connect(toEstimate, SIGNAL(clicked()), this, SLOT(invoiceToEstimate()));
    connect(exportToCSVButton, SIGNAL(clicked()), this, SLOT(exportToCSV()));
    connect(openAsSpreadsheetButton, SIGNAL(clicked()), this, SLOT(openAsSpreadSheet()));
}

void TodaysItemSalesWidget::setData(QDate dateEdit)
{
    QString searchQuery;
    if(searchKey->text() != "")
    {
        QString key;
        switch(searchType->currentIndex() +1)
        {
        case 1: key = searchKey->text() + "%"; break;
        case 2: key = "%" + searchKey->text(); break;
        case 3: key = searchKey->text(); break;
        case 4: key = "%" + searchKey->text() + "%"; break;
        }

        searchQuery += " " + searchBy->currentText() + " like '" + key + "'";
    }
    QString date;
    setHeader(Commons::getHeaderWithAddress() + "<br><center><b>Item Sales</b></center>");
    DatabaseServer server;
    date = dateEdit.toString("yyyy-MM-dd");
    itemDate = dateEdit;
    QString query = "select A.CommodityId, A.Commodity, B.PurchasePrice as 'Purchase Price', ";
    query += "A.Price as 'Sales Price', sum(A.Quantity) as Quantity, ";
    query += "A.PurchasePrice * sum(A.Quantity) as 'Purchase Total', ";
    query += "sum(A.GrossValue - Discount) as 'Sales Total', sum(A.Total) as 'Total Amount', ";
    query += "sum(A.GrossValue - Discount) - A.PurchasePrice * sum(A.Quantity) as Profit ";
    query += "from Invoice A left join Commodity B on A.CommodityId=B.Id ";
    query += "where Time like '" + date + "%' ";
    if(searchQuery != "")
    {
        query += " and " + searchQuery;
    }
    query += " group by Commodity";
    QStringList values = server.getListTableResult(query);

    table->setList(values);

    for(int i=0; i<table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width-50)/table->columnCount());
    }
    QString purchaseTotal = QString::number(table->getSumOfColumn(5));
    QString salesTotal = QString::number(table->getSumOfColumn(6));
    QString total = QString::number(table->getSumOfColumn(7));
    QString totalProfit = QString::number(table->getSumOfColumn(8));

    QString html = "<center><b><table width='70%'>";
    html += "<tr>";
    html += "<td>Total Purchase Amount: </td><td>" + purchaseTotal + "</td>";
    html += "<td>Total Sales Amount: </td><td>" + salesTotal + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>Total  Amount: </td><td>" + total + "</td>";
    html += "<td>Total Profit: </td><td>" + totalProfit + "</td>";
    html += "</tr></b></center>";

    setTotal(html);
}

void TodaysItemSalesWidget::setData(QString searchKey)
{
    QString searchQuery;
    if(searchKey != "")
    {
        QString key;
        switch(searchType->currentIndex() +1)
        {
        case 1: key = searchKey + "%"; break;
        case 2: key = "%" + searchKey; break;
        case 3: key = searchKey; break;
        case 4: key = "%" + searchKey + "%"; break;
        }

        searchQuery += " " + searchBy->currentText() + " like '" + key + "'";
    }
    QString date;
    setHeader(Commons::getHeaderWithAddress() + "<br><center><b>Item Sales</b></center>");
    DatabaseServer server;
    date = itemDate.toString("yyyy-MM-dd");
    QString query = "select A.CommodityId, A.Commodity, B.PurchasePrice as 'Purchase Price', ";
    query += "A.Price as 'Sales Price', sum(A.Quantity) as Quantity, ";
    query += "A.PurchasePrice * sum(A.Quantity) as 'Purchase Total', ";
    query += "sum(A.GrossValue - Discount) as 'Sales Total', sum(A.Total) as 'Total Amount', ";
    query += "sum(A.GrossValue - Discount) - A.PurchasePrice * sum(A.Quantity) as Profit ";
    query += "from Invoice A left join Commodity B on A.CommodityId=B.Id ";
    query += "where Time like '" + date + "%' ";
    if(searchQuery != "")
    {
        query += " and " + searchQuery;
    }
    query += " group by Commodity";
    QStringList values = server.getListTableResult(query);

    table->setList(values);

    for(int i=0; i<table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width-50)/table->columnCount());
    }
    QString purchaseTotal = QString::number(table->getSumOfColumn(5));
    QString salesTotal = QString::number(table->getSumOfColumn(6));
    QString total = QString::number(table->getSumOfColumn(7));
    QString totalProfit = QString::number(table->getSumOfColumn(8));

    QString html = "<center><b><table width='70%'>";
    html += "<tr>";
    html += "<td>Total Purchase Amount: </td><td>" + purchaseTotal + "</td>";
    html += "<td>Total Sales Amount: </td><td>" + salesTotal + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>Total  Amount: </td><td>" + total + "</td>";
    html += "<td>Total Profit: </td><td>" + totalProfit + "</td>";
    html += "</tr></b></center>";

    setTotal(html);
}

void TodaysItemSalesWidget::printReport()
{
  /*  QString date = itemDate.toString("dd-MM-yyyy");
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
    out<<"<br><br><center><b>" + Commons::insertNbspInBetween("Item Sales: ", 1) + Commons::insertNbspInBetween(date, 1) + "</b></center><br>";
    out<<"<br><table width='100%' id='tab'>";
    out<<"<tr><td id='tabd'>" + Commons::insertNbspInBetween("SlNo", 1) + "</td>";
    for(int i = 0; i < table->columnCount(); i++)
        out<<"<td id='tabd'>" + Commons::insertNbspInBetween(table->getHeader(i), 1) + "</td>";
    out<<"</tr>";
    for(int i = 0; i < table->rowCount(); i++)
    {
        out<<"<tr><td id='tabd'>" + QString::number(i + 1) + "</td>";
        for(int j = 0; j < table->columnCount(); j++)
            out<<"<td id='tabd'>" + Commons::insertNbspInBetween(table->getItem(i, j),1) + "</td>";
        out<<"</tr>";
    }
    int tot = table->getSumOfColumn(2) + 0.99;
    out<<"<td id='tabd' colspan=2><b><center>" + Commons::insertNbspInBetween("Total: ", 1) + "<center></b></td><td id='tabd'><b><fonnt size=5>" + Commons::insertNbspInBetween(QString::number(tot), 1) + "</font></b></td></tr>";
    out<<"</table>";

    // Html to PDF conversion
    QString htmlContent = out.readAll();
    Commons::htmlToPDF(filename, htmlContent);

    PrintViewDialog dialog;

    if(dialog.setwebView(htmlContent))
    {
        Commons::printHTML(htmlContent);
    }*/

    QStringList reportData;
    reportData.append(itemDate.toString("dd-MM-yy"));
    QStringList tableData;
    for(int i =0; i < table->rowCount(); i++)
    {
        QString column;
        for(int j = 0; j < table->columnCount(); j++)
        {
            column += table->getItem(i, j);
            if(j != table->columnCount()-1)
                column += "\n";
        }
        tableData.append(column);
    }

    reportData.append(QString::number(table->getSumOfColumn(5)));
    reportData.append(QString::number(table->getSumOfColumn(6)));
    reportData.append(QString::number(table->getSumOfColumn(7)));
    reportData.append(QString::number(table->getSumOfColumn(8)));
    PrintModule *pm = new PrintModule;
    pm->setPreviewMode(true);
    pm->setNoOfCopies(1);
    pm->setFilename("ItemSales.html");
    pm->printReportHtml(reportData, tableData);
}

void TodaysItemSalesWidget::invoiceToEstimate()
{
    qDebug()<<"Invoice to Estimate";
    TableInvoice::invoiceToEstimate("nx", dateEdit->date(), dateEdit->date());
}

void TodaysItemSalesWidget::exportToCSV()
{
    QString filename = QFileDialog::getSaveFileName();

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<"Date,"<<dateEdit->date().toString("dd-MM-yyyy")<<"\n\n";
    out<<table->toCommaSeperated();
    out<<"\nTotal,,,,,"<<table->getSumOfColumn(5, table->rowCount())<<","<<table->getSumOfColumn(6, table->rowCount())<<","<<table->getSumOfColumn(7, table->rowCount())<<","<<table->getSumOfColumn(8, table->rowCount());
}

void TodaysItemSalesWidget::openAsSpreadSheet()
{
    QString filename = "sample.csv";

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<"Date,"<<dateEdit->date().toString("dd-MM-yyyy")<<"\n\n";
    out<<table->toCommaSeperated();
    out<<"\nTotal,,,,,"<<table->getSumOfColumn(5, table->rowCount())<<","<<table->getSumOfColumn(6, table->rowCount())<<","<<table->getSumOfColumn(7, table->rowCount())<<","<<table->getSumOfColumn(8, table->rowCount());
    Commons::openFileOnDefaultApplication(filename);
}
