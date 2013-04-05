#include "dailysalesreportwidget.h"
#include <QtGui>
#include "databaseserver.h"
#include "commons.h"
#include <QtWebKit>
#include "printviewdialog.h"
#include "tableinvoice.h"

DailySalesReportWidget::DailySalesReportWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *header = new QLabel;
    header->setText(Commons::getHeaderWithAddress() + "<br><center><b>Sales Report<br></b></center>");
    QLabel *label1 = new QLabel("Date between ");
    QLabel *label2 = new QLabel("<center> And </center>");

    QDateEdit *dateEdit1 = new QDateEdit;
    QDateEdit *dateEdit2 = new QDateEdit;
    dateEdit1->setDate(QDate::currentDate());
    dateEdit2->setDate(QDate::currentDate());
    date1 = QDate::currentDate();
    date2 = QDate::currentDate();
    normalView = new QRadioButton("Normal View");
    normalView->setChecked(true);
    taxView = new QRadioButton("Tax View");
    hlay2->addStretch();
    hlay2->addWidget(label1);
    hlay2->addWidget(dateEdit1);
    hlay2->addStretch();
    hlay2->addWidget(label2);
    hlay2->addStretch();
    hlay2->addWidget(dateEdit2);
    hlay2->addStretch();
    hlay2->addWidget(normalView);
    hlay2->addWidget(taxView);
    table = new ListTableWidget;
    QLabel *total = new QLabel;
    QPushButton *print = new QPushButton("Print");
    QPushButton *exportToCSVButton = new QPushButton("Export to CSV");
    QPushButton *openAsSpreadsheetButton = new QPushButton("Open as Spreadsheet");
    print->setMaximumWidth(150);
    exportToCSVButton->setMaximumWidth(150);
    openAsSpreadsheetButton->setMaximumWidth(150);
    hlay1->addWidget(print);
    hlay1->addWidget(exportToCSVButton);
    hlay1->addWidget(openAsSpreadsheetButton);
    hlay1->addWidget(total);

    mainLayout->addWidget(header);
    mainLayout->addLayout(hlay2);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay1);

    connect( dateEdit1, SIGNAL(dateChanged(QDate)), this, SLOT(setDate1(QDate)));
    connect( dateEdit2, SIGNAL(dateChanged(QDate)), this, SLOT(setDate2(QDate)));
    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(print, SIGNAL(clicked()), this, SLOT(printReport()));
    connect(exportToCSVButton, SIGNAL(clicked()), this, SLOT(exportToCSV()));
    connect(openAsSpreadsheetButton, SIGNAL(clicked()), this, SLOT(openAsSpreadSheet()));
    connect( normalView, SIGNAL(clicked()), this, SLOT(setData()));
    connect( taxView, SIGNAL(clicked()), this, SLOT(setData()));
}

void DailySalesReportWidget::setDate1(QDate date)
{
    date1 = date;
    setData();
}

void DailySalesReportWidget::setDate2(QDate date)
{
    date2 = date;
    setData();
}

void DailySalesReportWidget::setData()
{
    QStringList values;
    if(normalView->isChecked())
    {
        DatabaseServer server;
        values = server.getListTableResult(" select  date_format(Date(A.Time),'%d/%m/%Y') as Date, A.InvoiceNo, B.Name, sum(A.TaxableValue) as Sales, sum(A.TaxAmount) as Tax, sum(A.Total) as Total from Invoice A left join Customers B on A.CustomerId=B.SlNo where A.Time >= '" + date1.toString("yyyy-MM-dd") + "' and A.Time <= '" + date2.toString("yyyy-MM-dd") +"' group by InvoiceNo;");
    }
    else
    {
        QStringList distinctTaxes = TableInvoice::getDistinctTaxInBetweenDates(date1, date2);
        DatabaseServer server;
        QString query = "select  date_format(Date(A.Time),'%d/%m/%Y') as Date, A.InvoiceNo, B.Name, ";
        for(int i = 0; i < distinctTaxes.size(); i++)
        {
            query += "sum(case Tax WHEN " + distinctTaxes.at(i) + " then TaxableValue END) as 'Sales Value T@" + distinctTaxes.at(i) + "%', ";
        }
        query += "sum(A.TaxableValue) as 'Total Sales', sum(A.TaxAmount) as 'Output Tax', sum(A.Total) as Total from Invoice A left join Customers B on A.CustomerId=B.SlNo where A.Time >= '" + date1.toString("yyyy-MM-dd") + "' and A.Time <= '" + date2.toString("yyyy-MM-dd") +"' group by InvoiceNo";
        values = server.getListTableResult(query);
    }

    table->setList(values);

    for(int i=0; i<table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width-50)/table->columnCount());
    }
    QString total = QString::number(table->getSumOfColumn(table->columnCount() -1));
    QString sales = QString::number(table->getSumOfColumn(table->columnCount() - 3));
    QString tax = QString::number(table->getSumOfColumn(table->columnCount() - 2));

    setTotal("<font size=4><center><b>Grand Total: " + Commons::getCommaSeperatedValue(total) + "<font size=4><center><b>Total Sales: " + Commons::getCommaSeperatedValue(sales) );
}

void DailySalesReportWidget::printReport()
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString filename = "SalesReport.pdf";
    QString content;
    QTextStream out(&content);
    QStringList htmlContent;
    QString allContent;
    int rowCount = 0;
    int maxItems = 22;
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
        out<<"<br><br><center><b>" + Commons::insertNbspInBetween("Sales Report: ", 1) + Commons::insertNbspInBetween(date1.toString("dd/MM/yyyy"), 1) + Commons::insertNbspInBetween(" to ", 1) + Commons::insertNbspInBetween(date2.toString("dd/MM/yyyy"), 1) + "</b></center><br>";
        out<<"<br><table width='100%' id=tab>";
        out<<"<tr><td id='tabd'>" + Commons::insertNbspInBetween("SlNo", 1) + "</td>";
        for(int i = 0; i < table->columnCount(); i++)
            out<<"<td id='tabd'><center>" + Commons::insertNbspInBetween(table->getHeader(i), 1) + "</center></td>";
        out<<"</tr>";
        if(rowCount > 0)
        {
            QString tot = QString::number(table->getSumOfColumn(5, rowCount));
            QString salesTot = QString::number((table->getSumOfColumn(3, rowCount)));
            QString vatTot = QString::number((table->getSumOfColumn(4, rowCount)));
            out<<"<tr><td colspan=3 id='tabd'><center>" + Commons::insertNbspInBetween("Grand Total ", 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(tot, 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(salesTot, 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(vatTot, 1) + "</center></td></tr>";
        }
        for(int i = rowCount; i < table->rowCount() && i < (rowCount + maxItems); i++)
        {
            out<<"<tr><td id='tabd'><center>" + Commons::insertNbspInBetween(QString::number(i + 1), 1) + "</center></td>";
            for(int j = 0; j < table->columnCount(); j++)
                out<<"<td id='tabd'><center>" + Commons::insertNbspInBetween(table->getItem(i, j), 1) + "</center></td>";
            out<<"</tr>";
        }

        rowCount += maxItems;

        if(rowCount >= table->rowCount())
        {
            QString tot = QString::number(table->getSumOfColumn(5, rowCount));
            QString salesTot = QString::number((table->getSumOfColumn(3, rowCount)));
            QString vatTot = QString::number((table->getSumOfColumn(4, rowCount)));
//            for(int i = table->rowCount() -1 ; i < rowCount; i++)
//            {
//                out<<"<tr>";
//                for(int j = 0; j < table->columnCount() + 1; j++)
//                    out<<"<td id=tabd>&nbsp;</td>";
//                out<<"</tr>";
//            }
            out<<"<tr><td colspan=3 id='tabd'><center>" + Commons::insertNbspInBetween("Grand Total ", 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(tot, 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(salesTot, 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(vatTot, 1) + "</center></td></tr>";
            out<<"</table>";
        }
        else
        {
            QString tot = QString::number(table->getSumOfColumn(5, rowCount));
            QString salesTot = QString::number((table->getSumOfColumn(3, rowCount)));
            QString vatTot = QString::number((table->getSumOfColumn(4, rowCount)));
            out<<"<tr><td colspan=3 id='tabd'><center>" + Commons::insertNbspInBetween("Grand Total ", 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(tot, 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(salesTot, 1) + "</center></td><td id='tabd'><center>" + Commons::insertNbspInBetween(vatTot, 1) + "</center></td></tr>";
            out<<"</table>";
            out<<"Continued......";
        }
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

void DailySalesReportWidget::exportToCSV()
{
    QString filename = QFileDialog::getSaveFileName();

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<"From (Date),"<<date1.toString("dd-MM-yyyy")<<",,To (Date),"<<date2.toString("dd-MM-yyyy")<<"\n\n";
    out<<table->toCommaSeperated();
    out<<"\nTotal,,";
    for(int i = 3; i < table->columnCount(); i++)
        out<<","<<table->getSumOfColumn(i, table->rowCount());
}

void DailySalesReportWidget::openAsSpreadSheet()
{
    QString filename = "sample.csv";

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<"From (Date),"<<date1.toString("dd-MM-yyyy")<<",,To (Date),"<<date2.toString("dd-MM-yyyy")<<"\n\n";
    out<<table->toCommaSeperated();
    out<<"\nTotal,,";
    for(int i = 3; i < table->columnCount(); i++)
        out<<","<<table->getSumOfColumn(i, table->rowCount());
    Commons::openFileOnDefaultApplication(filename);
}

QString DailySalesReportWidget::getCommas(int count)
{
    QString commas ="";
    for(int i = 0; i < count; i++)
    {
        commas += ",";
    }

    return commas;
}
