#include "purchaseditemwidget.h"
#include <QtGui>
#include <QtWebKit>
#include "commons.h"
#include "databaseserver.h"
#include "printviewdialog.h"
#include "printmodule.h"
#include "tableinvoice.h"

#define INPUT_WIDTH 150

PurchasedItemWidget::PurchasedItemWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *header = new QLabel;

    dateStart = new QDateEdit();
    dateStart->setDate(QDate::currentDate());
    dateEnd = new QDateEdit;
    dateEnd->setDate(QDate::currentDate());
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
    QLabel *label1 = new QLabel("Date Between ");
    QLabel *label2 = new QLabel("Search By ");
    QLabel *label3 = new QLabel(" Search Key ");
    QLabel *label4 = new QLabel(" and ");
    QLabel *total = new QLabel;
    QPushButton *print = new QPushButton("Print");
    QPushButton *exportToCSVButton = new QPushButton("Export to CSV");
    QPushButton *openAsSpreadsheetButton = new QPushButton("Open as Spreadsheet");
    print->setMaximumWidth(150);
    exportToCSVButton->setMaximumWidth(150);
    openAsSpreadsheetButton->setMaximumWidth(150);

    hlay2->addWidget(label2);
    hlay2->addWidget(searchBy);
    hlay2->addWidget(searchType);
    hlay2->addWidget(label3);
    hlay2->addWidget(searchKey);
    hlay2->addStretch();
    hlay2->addWidget(label1);
    hlay2->addWidget(dateStart);
    hlay2->addWidget(label4);
    hlay2->addWidget(dateEnd);
    hlay2->addStretch();
    hlay1->addWidget(print);
    hlay1->addWidget(exportToCSVButton);
    hlay1->addWidget(openAsSpreadsheetButton);
    hlay1->addWidget(total);

    mainLayout->addWidget(header);
    mainLayout->addLayout(hlay2);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay1);

    connect(dateStart, SIGNAL(dateChanged(QDate)), this, SLOT(setData(QDate)));
    connect(dateEnd, SIGNAL(dateChanged(QDate)), this, SLOT(setData(QDate)));
    connect(searchKey, SIGNAL(textChanged(QString)), this, SLOT(setData(QString)));
    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(print, SIGNAL(clicked()), this, SLOT(printReport()));
    connect(exportToCSVButton, SIGNAL(clicked()), this, SLOT(exportToCSV()));
    connect(openAsSpreadsheetButton, SIGNAL(clicked()), this, SLOT(openAsSpreadSheet()));
}

void PurchasedItemWidget::setData(QDate dateEdit)
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
    setHeader(Commons::getHeaderWithAddress() + "<br><center><b>Item Purchases</b></center>");
    DatabaseServer server;
    date = dateEdit.toString("yyyy-MM-dd");
    itemDate = dateEdit;
    QString query = "select A.CommodityId, A.Commodity, B.PurchasePrice as 'Purchase Price', ";
    query += " sum(A.Quantity) as Quantity, ";
    query += "A.PurchasePrice * sum(A.Quantity) as 'Purchase Total', ";
    query += "sum(A.Total) as 'Total Amount' ";
    query += "from StockInvoice A left join Commodity B on A.CommodityId=B.Id ";
    query += "where Time >= '" + dateStart->date().toString("yyyy-MM-dd") + "' and Time <= '" + dateEnd->date().toString("yyyy-MM-dd") + "'";
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
    QString purchaseTotal = QString::number(table->getSumOfColumn(4));
    QString total = QString::number(table->getSumOfColumn(5));

    QString html = "<center><b><table width='70%'>";
    html += "<tr>";
    html += "<td>Total Purchase Amount: </td><td>" + purchaseTotal + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>Total  Amount: </td><td>" + total + "</td>";
    html += "</tr></b></center>";

    setTotal(html);
}

void PurchasedItemWidget::setData(QString searchKey)
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
    query += " sum(A.Quantity) as Quantity, ";
    query += "A.PurchasePrice * sum(A.Quantity) as 'Purchase Total', ";
    query += "sum(A.Total) as 'Total Amount' ";
    query += "from StockInvoice A left join Commodity B on A.CommodityId=B.Id ";
    query += "where Time >= '" + dateStart->date().toString("yyyy-MM-dd") + "' and Time <= '" + dateEnd->date().toString("yyyy-MM-dd") + "'";
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
    QString purchaseTotal = QString::number(table->getSumOfColumn(4));
    QString total = QString::number(table->getSumOfColumn(5));

    QString html = "<center><b><table width='70%'>";
    html += "<tr>";
    html += "<td>Total Purchase Amount: </td><td>" + purchaseTotal + "</td>";
    html += "</tr>";
    html += "<tr>";
    html += "<td>Total  Amount: </td><td>" + total + "</td>";
    html += "</tr></b></center>";

    setTotal(html);
}

void PurchasedItemWidget::printReport()
{
    QStringList reportData;
    reportData.append(itemDate.toString("dd/MM/yyyy"));
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

    reportData.append(QString::number(table->getSumOfColumn(4)));
    reportData.append(QString::number(table->getSumOfColumn(5)));

    PrintModule *pm = new PrintModule;
    pm->setPreviewMode(true);
    pm->setNoOfCopies(1);
    pm->setDirecory("Prints");
    pm->setFilename("purchaseitemsreport.html");
    pm->printReportHtml(reportData, tableData);
}

void PurchasedItemWidget::exportToCSV()
{
    QString filename = QFileDialog::getSaveFileName();

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<"From (Date),"<<dateStart->date().toString("dd-MM-yyyy")<<",,To (Date),"<<dateStart->date().toString("dd-MM-yyyy")<<"\n\n";
    out<<table->toCommaSeperated();
    out<<"\nTotal,,,"<<table->getSumOfColumn(3, table->rowCount())<<","<<table->getSumOfColumn(4, table->rowCount())<<","<<table->getSumOfColumn(5, table->rowCount());
}

void PurchasedItemWidget::openAsSpreadSheet()
{
    QString filename = "sample.csv";

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<"From (Date),"<<dateStart->date().toString("dd-MM-yyyy")<<",,To (Date),"<<dateStart->date().toString("dd-MM-yyyy")<<"\n\n";
    out<<table->toCommaSeperated();
    out<<"\nTotal,,,"<<table->getSumOfColumn(3, table->rowCount())<<","<<table->getSumOfColumn(4, table->rowCount())<<","<<table->getSumOfColumn(5, table->rowCount());
    Commons::openFileOnDefaultApplication(filename);
}
