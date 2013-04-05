#include "historyitemsaleswidget.h"
#include <QtGui>
#include <QtWebKit>
#include "commons.h"
#include "databaseserver.h"
#include "printviewdialog.h"
#include "printmodule.h"

HistoryItemSalesWidget::HistoryItemSalesWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *header = new QLabel;
    dateStart = new QDateEdit;
    dateStart->setDate(QDate::currentDate());
    dateEnd = new QDateEdit;
    dateEnd->setDate(QDate::currentDate());
    QDateEdit *dateEdit = new QDateEdit();
    dateEdit->setDate(QDate::currentDate());
    table = new ListTableWidget;
    QLabel *label1 = new QLabel("Date Between: ");
    QLabel *label2 = new QLabel(" and ");
    QLabel *total = new QLabel;
    QPushButton *print = new QPushButton("Print");
    QPushButton *exportToCSVButton = new QPushButton("Export to CSV");
    QPushButton *openAsSpreadsheetButton = new QPushButton("Open as Spreadsheet");
    print->setMaximumWidth(150);
    exportToCSVButton->setMaximumWidth(150);
    openAsSpreadsheetButton->setMaximumWidth(150);
    hlay2->addStretch();
    hlay2->addWidget(label1);
    hlay2->addWidget(dateStart);
    hlay2->addWidget(label2);
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
    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(print, SIGNAL(clicked()), this, SLOT(printReport()));
    connect(exportToCSVButton, SIGNAL(clicked()), this, SLOT(exportToCSV()));
    connect(openAsSpreadsheetButton, SIGNAL(clicked()), this, SLOT(openAsSpreadSheet()));
}

void HistoryItemSalesWidget::setData(QDate dateEdit)
{
    QString date;
    setHeader(Commons::getHeaderWithAddress() + "<br><center><b>History Item Sales</b></center>");
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
    query += "where Time >= '" + dateStart + "' and Time <= '" + dateEnd + "' group by Commodity";
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

void HistoryItemSalesWidget::printReport()
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

void HistoryItemSalesWidget::exportToCSV()
{
    QString filename = QFileDialog::getSaveFileName();

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<"From (Date),"<<dateStart->date().toString("dd-MM-yyyy")<<",,To (Date),"<<dateEnd->date().toString("dd-MM-yyyy")<<"\n\n";
    out<<table->toCommaSeperated();
    out<<"\nTotal,,,,,"<<table->getSumOfColumn(5, table->rowCount())<<","<<table->getSumOfColumn(6, table->rowCount())<<","<<table->getSumOfColumn(7, table->rowCount())<<","<<table->getSumOfColumn(8, table->rowCount());
}

void HistoryItemSalesWidget::openAsSpreadSheet()
{
    QString filename = "sample.csv";

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<"From (Date),"<<dateStart->date().toString("dd-MM-yyyy")<<",,To (Date),"<<dateEnd->date().toString("dd-MM-yyyy")<<"\n\n";
    out<<table->toCommaSeperated();
    out<<"\nTotal,,,,,"<<table->getSumOfColumn(5, table->rowCount())<<","<<table->getSumOfColumn(6, table->rowCount())<<","<<table->getSumOfColumn(7, table->rowCount())<<","<<table->getSumOfColumn(8, table->rowCount());
    Commons::openFileOnDefaultApplication(filename);
}
