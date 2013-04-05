#include "historyinvoicewidget.h"
#include <QtGui>
#include "commons.h"
#include "databaseserver.h"
#include "printviewdialog.h"

HistoryInvoiceWidget::HistoryInvoiceWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;

    QHBoxLayout *hlay1, *hlay2;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;

    QRegExp regExp("[0-9]*([.][0-9]*)?");
    QLabel *header = new QLabel(Commons::getHeaderWithAddress());
    QLabel *label1 = new QLabel("InvoiceNo:");
    invoiceNo = new QLineEdit;
    invoiceNo->setValidator(new QRegExpValidator(regExp, this));
    QLabel *details = new QLabel;
    details->setMinimumHeight(100);
    table = new ListTableWidget;
    QPushButton *print = new QPushButton("Print");
    print->setMaximumWidth(150);
    QLabel *total = new QLabel;

    hlay1->addStretch();
    hlay1->addWidget(label1);
    hlay1->addWidget(invoiceNo);
    hlay1->addStretch();

    hlay2->addWidget(print);
    hlay2->addWidget(total);

    mainLayout->addWidget(header);
    mainLayout->addLayout(hlay1);
    mainLayout->addWidget(details);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay2);

    connect(this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect(this, SIGNAL(setDetails(QString)), details, SLOT(setText(QString)));
    connect(this, SIGNAL(setTotal(QString)), total, SLOT(setText(QString)));
    connect(invoiceNo, SIGNAL(textChanged(QString)), this, SLOT(setData()));
    connect(print, SIGNAL(clicked()), this, SLOT(printInvoice()));
}

void HistoryInvoiceWidget::setData()
{
    DatabaseServer server;
    QString details;
    details = "<center><b>Details of the Purchasing Dealer</b></center>";
    if(invoiceNo->text() != "")
    {
        dealerId = server.getRowResult("select DealerId,Dealer,Tin from DealerInvoice where InvoiceNo=" + invoiceNo->text());
        if(dealerId.size())
        {
            invoiceDate = server.getSingleResult("select Time from Invoice where InvoiceNo=" + invoiceNo->text()).split("T").at(0);
            details += "<center><b><br>Dealer Id: " + dealerId.at(0) + "<br>Dealer Name: " + dealerId.at(1) + "<br>Tin No: " + dealerId.at(2) + "</center>" + "Date: " + invoiceDate + "</b>";
        }
        QStringList tableContent = server.getListTableResult("select Commodity,Tax,Price,Quantity,Gift,GrossValue,Discount,TaxableValue,TaxAmount,Cess,Total from Invoice where InvoiceNo=" + invoiceNo->text());
        table->setList(tableContent);
        if(tableContent.size())
        {
            for(int i=0; i<table->columnCount(); i++)
            {
                table->setColumnWidth(i,(width-50)/table->columnCount());
            }
        }
    }
    setDetails(details);
    setTotal("<center><b><font size=5>" + QString::number(table->getSumOfColumn(10)) + "</b></center>");
}

void HistoryInvoiceWidget::printInvoice()
{
    if(table->rowCount() < 1)
        return;
    QString content;
    QTextStream out(&content);
    QStringList htmlContent;
    int ind = 0;
    QString allContent;
    int rowCount = 0;
    int maxItems = 7;
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
        out<<"<br>" + Commons::insertNbspInBetween("Invoice No: ",1) + Commons::insertNbspInBetween(Commons::getInvoiceNo(),1) + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" +  Commons::insertNbspInBetween("Date: ", 1) +  Commons::insertNbspInBetween(invoiceDate, 1) + "</center>";
        out<<"</font><center>" + Commons::insertNbspInBetween("FORM 8",1);
        out<<"<br>" +Commons::insertNbspInBetween("KVAT RULES 2005",1);
        out<<"--&nbsp;&nbsp;" + Commons::insertNbspInBetween("TAX INVOICE",1) + "--&nbsp;&nbsp;" + Commons::insertNbspInBetween("CASH/CREDIT",1) + "</center>";
        out<<"<center><b>" + Commons::insertNbspInBetween("Details of Purchasing Dealer", 1) + "</b>";
        out<<"<table width='100%'>";
        out<<"<tr><td>Id: </td><td>" + dealerId.at(0) + "</td><td>Name: </td><td>" + dealerId.at(1) + "</td><td>Tin No: </td><td>" + dealerId.at(2) + "</td></tr>";
        out<<"</table>";
        out<<"<br><table cellspacing='0' width='100%' id=tab>";
        out<<"<tr><td id=tabd width='5%'>SlNo</td>";
        for(int i = 1; i < table->columnCount(); i++)
            out<<"<td id=tabd><font size=2>" + Commons::insertNbspInBetween(table->getHeader(i),1) + "&nbsp;&nbsp;</font></td>";
        out<<"</tr>";
        for(int i = rowCount; i < table->rowCount() && i < (rowCount + maxItems); i++)
        {
            out<<"<tr><td id=tabd>" + QString::number(i + 1) + "</td>";
            for(int j = 1; j < table->columnCount(); j++)
                out<<"<td id=tabd><font size=2>" + Commons::insertNbspInBetween(table->getItem(i, j),1) + "</font></td>";
            out<<"</tr>";
        }
        rowCount += maxItems;

        if(rowCount > table->rowCount())
        {
            for(int i = table->rowCount() -1 ; i < rowCount; i++)
            {
                out<<"<tr>";
                for(int j = 0; j < table->columnCount(); j++)
                    out<<"<td id=tabd>&nbsp;</td>";
                out<<"</tr>";
            }

            int tot = table->getSumOfColumn(10) + 0.99;
            out<<"<tr><td  id=tabd colspan=5><b><center>" + Commons::insertNbspInBetween("Reduction: ", 1) + "<center></b></td  id=tabd><td colspan=5><b><center>" + Commons::insertNbspInBetween("Total: ",1) + "<center></b></td><td colspan=2><b>" + Commons::insertNbspInBetween(QString::number(tot),1) + "</b></td></tr>";
            out<<"<tr><td colspan=7 id=tabd><b>" + Commons::insertNbspInBetween("Grand Total in Words: ",1) + "</b></td><td colspan=6 id=tabd><b><fonnt size=5>" + Commons::insertNbspInBetween(Commons::numberToWords(tot),1) + "</b></td></tr>";
            out<<"</table></center>";
            out<<"<br><i>" + Commons::insertNbspInBetween("Terms of delivery and payment if any", 1) + "</i>";
            out<<"<center><b><u>" + Commons::insertNbspInBetween("Declaration", 1) + "</u></b></center>";
            out<<"<br><font size=2>" + Commons::insertNbspInBetween("Certified that all the particulars shown in the above tax invoice are true and correct and that my/our Registration under KVAT Act 2003 is valid as on the date of this bill.", 1) + "</font>";
            out<<"<br>" + Commons::insertNbspInBetween("Authorised Signatory", 1);
            out<<"</body></html>";;
        }
        else
        {
            out<<"</table></body></html>";
        }
        htmlContent.append(out.readAll());
        if(rowCount < table->rowCount())
            allContent += htmlContent.at(ind);
        else
            allContent += htmlContent.at(ind);

        ind++;

    }while(rowCount < table->rowCount());

    PrintViewDialog dialog;

    if(dialog.setwebView(allContent))
    {
        for(int i = 0; i < htmlContent.size(); i++)
            Commons::printHTML(htmlContent.at(i));
    }

//    Commons::openFileOnDefaultApplication(filename);
}
