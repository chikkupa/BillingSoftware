#include "itemestimatewidget.h"
#include <QtGui>
#include <QtWebKit>
#include "commons.h"
#include "databaseserver.h"
#include "printviewdialog.h"
#include "printmodule.h"
#include "tableinvoice.h"

ItemEstimateWidget::ItemEstimateWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    mainLayout = new QVBoxLayout(this);

}

void ItemEstimateWidget::setData()
{
    delete mainLayout;
    mainLayout = new QVBoxLayout(this);
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;

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
    print->setMaximumWidth(150);

    hlay2->addWidget(label2);
    hlay2->addWidget(searchBy);
    hlay2->addWidget(searchType);
    hlay2->addWidget(label3);
    hlay2->addWidget(searchKey);
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

    connect(dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setTable(QDate)));
    connect(searchKey, SIGNAL(textChanged(QString)), this, SLOT(setTable(QString)));
    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(print, SIGNAL(clicked()), this, SLOT(printReport()));

    setTable();
}

void ItemEstimateWidget::setTable(QDate dateEdit)
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
    setHeader(Commons::getHeaderWithAddress() + "<br><center><b>Item Estimates</b></center>");
    DatabaseServer server;
    date = dateEdit.toString("yyyy-MM-dd");
    itemDate = dateEdit;
    QString query = "select A.CommodityId, A.Commodity, B.PurchasePrice as 'Purchase Price', ";
    query += "A.Price as 'Sales Price', sum(A.Quantity) as Quantity, ";
    query += "A.PurchasePrice * sum(A.Quantity) as 'Purchase Total', ";
    query += "sum(A.GrossValue - Discount) as 'Sales Total', sum(A.Total) as 'Total Amount', ";
    query += "sum(A.GrossValue - Discount) - A.PurchasePrice * sum(A.Quantity) as Profit ";
    query += "from Estimate A left join Commodity B on A.CommodityId=B.Id ";
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

void ItemEstimateWidget::setTable(QString searchKey)
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
    query += "from Estimate A left join Commodity B on A.CommodityId=B.Id ";
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

void ItemEstimateWidget::printReport()
{
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
