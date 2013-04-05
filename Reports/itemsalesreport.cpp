#include "itemsalesreport.h"
#include <QtGui>
#include <QtWebKit>
#include "commons.h"
#include "databaseserver.h"
#include "printviewdialog.h"
#include "printmodule.h"
#include "globalcache.h"
#include "tablecommodity.h"
#include "getserialnodialog.h"

#define INPUT_WIDTH 150

ItemSalesReport::ItemSalesReport(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Item Sales Report");
    width = GlobalCache::getScreenWidth();
    int height = GlobalCache::getScreenHeight();
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *header = new QLabel;
    dateStart = new QDateEdit;
    dateStart->setDate(QDate::currentDate());
    dateEnd = new QDateEdit;
    dateEnd->setDate(QDate::currentDate());
    commodityId = new QComboBox;
    commodityId->setMinimumWidth(INPUT_WIDTH);
    commodityId->setEditable(true);
    commodityName = new QComboBox;
    commodityName->setMinimumWidth(INPUT_WIDTH);
    commodityName->setEditable(true);
    QPushButton *addItem = new QPushButton("Add");
    QPushButton *removeItem = new QPushButton("Remove");
    QDateEdit *dateEdit = new QDateEdit();
    dateEdit->setDate(QDate::currentDate());
    table = new ListTableWidget;

    QLabel *label1 = new QLabel("Date Between: ");
    QLabel *label2 = new QLabel(" and ");
    QLabel *label3 = new QLabel("Id: ");
    QLabel *label4 = new QLabel("Name: ");
    QLabel *total = new QLabel;
    QPushButton *print = new QPushButton("Print");
    QPushButton *close = new QPushButton("Close");
    close->setMaximumWidth(150);
    close->setDefault(true);
    print->setMaximumWidth(150);
    hlay2->addStretch();
    hlay2->addWidget(label1);
    hlay2->addWidget(dateStart);
    hlay2->addWidget(label2);
    hlay2->addWidget(dateEnd);
    hlay2->addStretch();
    hlay1->addWidget(print);
    hlay1->addWidget(total);
    hlay1->addWidget(close);
    hlay2->addStretch();
    hlay2->addWidget(label3);
    hlay2->addWidget(commodityId);
    hlay2->addStretch();
    hlay2->addWidget(label4);
    hlay2->addWidget(commodityName);
    hlay2->addWidget(addItem);
    hlay2->addWidget(removeItem);
    hlay2->addStretch();

    mainLayout->addWidget(header);
    mainLayout->addLayout(hlay2);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay1);

    connect(dateStart, SIGNAL(dateChanged(QDate)), this, SLOT(setData(QDate)));
    connect(dateEnd, SIGNAL(dateChanged(QDate)), this, SLOT(setData(QDate)));
    connect(commodityId, SIGNAL(currentIndexChanged(int)), commodityName, SLOT(setCurrentIndex(int)));
    connect(commodityName, SIGNAL(currentIndexChanged(int)), commodityId, SLOT(setCurrentIndex(int)));
    connect(addItem, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(removeItem, SIGNAL(clicked()), this, SLOT(removeItem()));
    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(print, SIGNAL(clicked()), this, SLOT(printReport()));
    connect(close, SIGNAL(clicked()), this, SLOT(accept()));

    showMaximized();
}

void ItemSalesReport::getItemSales()
{
    QStringList values;
    values.append("CommodityId\nCommodity\nPurchase Price\nSales Price\nQuantity\nPurchase Total\nSales Total\nTotal Amount\nProfit");
    table->setList(values);

    for(int i=0; i<table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width-50)/table->columnCount());
    }
    setHeader("<br><center><b>Item Sales Report</b></center>");
    QStringList ids;
    ids.append("");
    ids.append(TableCommodity::getCommodityIds());
    QStringList names;
    names.append("");
    names.append(TableCommodity::getCommodityNames());
    commodityId->addItems(ids);
    commodityName->addItems(names);

    QCompleter *completer1 = new QCompleter(commodityId);
    completer1->setCaseSensitivity(Qt::CaseInsensitive);
    QStringListModel *listModel1 = new QStringListModel(completer1);
    listModel1->setStringList(ids);
    completer1->setModel(listModel1);
    completer1->setCompletionMode(QCompleter::PopupCompletion);
    commodityId->setCompleter(completer1);

    QCompleter *completer2 = new QCompleter(commodityName);
    completer2->setCaseSensitivity(Qt::CaseInsensitive);
    QStringListModel *listModel2 = new QStringListModel(completer2);
    listModel2->setStringList(names);
    completer2->setModel(listModel2);
    completer2->setCompletionMode(QCompleter::PopupCompletion);
    commodityName->setCompleter(completer2);

    exec();
}

void ItemSalesReport::setData(QDate dateEdit)
{
    QString date;
    QString ids = "('";
    for(int i = 0; i < table->rowCount(); i++)
    {
        ids +=  table->getItem(i, 0);
        if(i < table->rowCount() - 1)
            ids += "','";
    }
    ids += "')";
    DatabaseServer server;
    date = dateEdit.toString("yyyy-MM-dd");
    QString dateStart = this->dateStart->date().toString("yyyy-MM-dd");
    QString dateEnd = this->dateEnd->date().toString("yyyy-MM-dd");
    itemDate = dateEdit;
    QString query = "select A.CommodityId, A.Commodity, B.PurchasePrice as 'Purchase Price', ";
    query += "A.Price as 'Sales Price', sum(A.Quantity) as Quantity, ";
    query += "A.PurchasePrice * sum(A.Quantity) as 'Purchase Total', ";
    query += "sum(A.GrossValue - Discount) as 'Sales Total', sum(A.Total) as 'Total Amount', ";
    query += "sum(A.GrossValue - Discount) - A.PurchasePrice * sum(A.Quantity) as Profit ";
    query += "from Invoice A left join Commodity B on A.CommodityId=B.Id ";
    query += "where Time >= '" + dateStart + "' and Time <= '" + dateEnd + "' and A.CommodityId in " + ids + " group by Commodity";
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

void ItemSalesReport::printReport()
{
    QStringList reportData;
    reportData.append(dateStart->date().toString("dd-MM-yy"));
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

void ItemSalesReport::checkCode()
{
}

void ItemSalesReport::addItem()
{
    QStringList result = TableCommodity::getItemSalesDetails(commodityId->currentText(), dateStart->date(), dateEnd->date());
    table->addEndRow(result.at(0));

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
    commodityId->setCurrentIndex(0);
    commodityName->setCurrentIndex(0);
}

void ItemSalesReport::removeItem()
{
    GetSerialNoDialog dialog;
    int serialNo = dialog.getSerialNo().toInt();
    if(serialNo > 0 && serialNo <= table->rowCount())
    {
        table->removeRow(serialNo - 1);
        commodityId->setFocus();
        getSummary();
    }
    else if(serialNo > 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Serial No");
        msgBox.setText("No item found on this serial number!");
        msgBox.exec();
    }
}

void ItemSalesReport::getSummary()
{
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
