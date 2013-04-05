#include "oldpurchaseinvoicewidget.h"
#include <QtGui>
#include "databaseserver.h"
#include "commons.h"
#include "getserialnodialog.h"
#include "tablestockinvoice.h"
#include "tablecustomers.h"
#include "printmodule.h"

#define MARGIN 0.50 // Margin for round off

OldPurchaseInvoiceWidget::OldPurchaseInvoiceWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4, *hlay5, *hlay6, *hlay7, *hlay8, *hlay9, *hlay10, *hlay11;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *vlay1;

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;
    hlay3 = new QHBoxLayout;
    hlay4 = new QHBoxLayout;
    hlay5 = new QHBoxLayout;
    hlay6 = new QHBoxLayout;
    hlay7 = new QHBoxLayout;
    hlay8 = new QHBoxLayout;
    hlay9 = new QHBoxLayout;
    hlay10 = new QHBoxLayout;
    hlay11 = new QHBoxLayout;

    vlay1 = new QVBoxLayout;

    QLabel *header = new QLabel;
    invoiceNo = new QSpinBox;
    int largest = Commons::getLargestInvoiceNo();
    invoiceNo->setMaximum(largest);
    invoiceNo->setMinimum(Commons::getSmallestInvoiceNo());
    invoiceNo->setValue(largest);
    currentInvoiceNo = QString::number(largest);
    QDateEdit *dateEdit = new QDateEdit;
    dateEdit->setDate(QDate::currentDate());
    invoiceDate = QDate::currentDate();

    QLabel *customerHead = new QLabel("<b><center>Dealer Details</center></b>");
    QLabel *label2 = new QLabel("Name: ");
    QLabel *label3 = new QLabel("Address: ");
    QLabel *label4 = new QLabel("Telephone: ");
    QLabel *label5 = new QLabel("Mobile: ");
    QLabel *label7 = new QLabel("Email: ");

    QLabel *commodityHead = new QLabel("<center><b>Item Details</b><center>");
    QLabel *label11 = new QLabel("Item Code: ");
    QLabel *label12 = new QLabel("Item Name: ");
    QLabel *label13 = new QLabel("Quantity: ");
    QLabel *label14 = new QLabel("Tax: ");
    QLabel *label15 = new QLabel("Rate: ");
    QLabel *label16 = new QLabel("Total: ");

    QLabel *label21 = new QLabel("<b>Date: </b>");
    QLabel *label22 = new QLabel("<b>InvoiceNo<b>");
    QLabel *lable23 = new QLabel("<b>STOCK PURCHASE DETAILS</b>");

    width = wid;

    id = new QComboBox;
    id->setEditable(true);
    id->setCompleter(id->completer());
    id->setMinimumWidth(150);
    name = new QLineEdit;
    address = new QLineEdit;
    phoneNo = new QLineEdit;
    mobile = new QLineEdit;
    email = new QLineEdit;

    QRegExp regExp("[0-9]*([.][0-9]*)?");
    comId = new QComboBox;
    comId->setEditable(true);
    comId->setMinimumWidth(150);
    comId->setFocus();
    commodity = new QComboBox;
    commodity->setEditable(true);
    commodity->setMinimumWidth(150);
    quantity = new QLineEdit;
    quantity->setValidator(new QRegExpValidator(regExp, this));
    tax = new QLineEdit;
    tax->setValidator(new QRegExpValidator(regExp, this));
    price = new QLineEdit;
    price->setValidator(new QRegExpValidator(regExp, this));
    QLineEdit *total = new QLineEdit;
    total->setValidator(new QRegExpValidator(regExp, this));

    QPushButton *addItem = new QPushButton("Add Item");
    addItem->setDefault(true);
    addItem->setShortcut(QKeySequence(tr("Ctrl+Space")));
    QPushButton *removeItem = new QPushButton("Remove Item");
    removeItem->setShortcut(QKeySequence(tr("Ctrl+Alt+Space")));
    QPushButton *removeLast = new QPushButton(this);
    removeLast->setMaximumWidth(0);
    removeLast->setShortcut(QKeySequence(tr("Ctrl+Shift+Space")));
    table = new ListTableWidget;

    QPushButton *print = new QPushButton("Print and Save");
    print->setMaximumWidth(150);
    print->setShortcut(QKeySequence(tr("Ctrl+S")));
    QPushButton *printOnly = new QPushButton("Print Only");
    printOnly->setMaximumWidth(150);
    printOnly->setShortcut(QKeySequence(tr("Ctrl+P")));
    QPushButton *save = new QPushButton("Save");
    save->setMaximumWidth(150);
    QLabel *grandTotal = new QLabel;

    hlay1->addWidget(label2);
    hlay1->addWidget(name);
    hlay1->addWidget(label3);
    hlay1->addWidget(address);
    hlay1->addWidget(label4);
    hlay1->addWidget(phoneNo);
    hlay1->addWidget(label5);
    hlay1->addWidget(mobile);
    hlay2->addWidget(label7);
    hlay2->addWidget(email);

    hlay3->addWidget(customerHead);

    hlay4->addWidget(label11);
    hlay4->addWidget(comId);
    hlay4->addWidget(label12);
    hlay4->addWidget(commodity);
    hlay4->addWidget(label13);
    hlay4->addWidget(quantity);;
    hlay4->addWidget(label14);
    hlay4->addWidget(tax);
    hlay4->addWidget(label15);
    hlay4->addWidget(price);
    hlay4->addWidget(label16);
    hlay4->addWidget(total);
    hlay4->addWidget(addItem);
    hlay4->addWidget(removeItem);
    hlay6->addWidget(commodityHead);
    hlay7->addWidget(print);
    hlay7->addWidget(printOnly);
    hlay7->addWidget(save);
    vlay1->addLayout(hlay8);
    vlay1->addLayout(hlay7);
    hlay9->addLayout(vlay1, 1);
    hlay9->addWidget(grandTotal, 2);
    hlay11->addWidget(label22);
    hlay11->addWidget(invoiceNo);
    hlay11->addStretch();
    hlay10->addWidget(label21);
    hlay10->addWidget(dateEdit);
    hlay10->addStretch();
    hlay10->addWidget(lable23);
    hlay10->addStretch();

    mainLayout->addWidget(header);
    mainLayout->addLayout(hlay11);
    mainLayout->addLayout(hlay10);
    mainLayout->addLayout(hlay3);
    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);
    mainLayout->addLayout(hlay6);
    mainLayout->addLayout(hlay4);
    mainLayout->addLayout(hlay5);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay9);

    connect( invoiceNo, SIGNAL(valueChanged(int)), this, SLOT(setInvoiceNo(int)));
    connect( dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setDate(QDate)));
    connect( this, SIGNAL(setDateEdit(QDate)), dateEdit, SLOT(setDate(QDate)));
    connect( comId, SIGNAL(currentIndexChanged(QString)), this, SLOT(checkCode(QString)));
    connect( commodity, SIGNAL(currentIndexChanged(int)), comId, SLOT(setCurrentIndex(int)));
    connect( addItem, SIGNAL(clicked()), this, SLOT(addAnItem()));
    connect( removeItem, SIGNAL(clicked()), this, SLOT(removeItem()));
    connect( removeLast,SIGNAL(clicked()), this, SLOT(removeLastItem()));
    connect( this, SIGNAL(setGrandTotal(QString)), grandTotal, SLOT(setText(QString)));
    connect( print, SIGNAL(clicked()), this, SLOT(printAndSave()));
    connect( printOnly, SIGNAL(clicked()), this, SLOT(printInvoiceHtml()));
    connect( save, SIGNAL(clicked()), this, SLOT(saveOnly()));
    connect( this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect( total, SIGNAL(textChanged(QString)), this, SLOT(totalCorrection(QString)));
    connect( addItem, SIGNAL(clicked()), total, SLOT(clear()));
}

void OldPurchaseInvoiceWidget::setData()
{
    clearCustomerData();
    int largest = Commons::getLargestPurchaseNo();
    invoiceNo->setMaximum(largest);
    invoiceNo->setValue(largest);

    setHeader(Commons::getHeaderWithAddress());
    tableValues.clear();
    tableValues.append("Item Code\nItem Name\nTax\nPurchase Price\nQty\nTaxable\nTax Amt\nTotal");
    tableValues.append(TableStockInvoice::getStockInvoiceDetails(invoiceNo->text()));

    QString custId = TableStockInvoice::getCustomerId(invoiceNo->text());
    QStringList custDetails = TableCustomers::getCustomerDetails(custId);
    if(custDetails.size())
    {
        name->setText(custDetails.at(0));
        address->setText(custDetails.at(1));
        phoneNo->setText(custDetails.at(2));
        mobile->setText(custDetails.at(3));
        email->setText(custDetails.at(4));
    }

    setDateEdit(TableStockInvoice::getDate(invoiceNo->text()));
    DatabaseServer server;
    comIds.clear();
    commodities.clear();
    comIds += "";
    commodities += "";
    comIds += server.getListResult("select Id from Commodity");
    commodities += server.getListResult("select Name from Commodity");
    comValues = server.getMultiListResult("select Id,Name,Tax,PurchasePrice,Cess from Commodity");
    comId->clear();
    commodity->clear();

    QCompleter *completer1 = new QCompleter(comId);
    completer1->setCaseSensitivity(Qt::CaseInsensitive);
    QStringListModel *listModel1 = new QStringListModel(completer1);
    listModel1->setStringList(comIds);
    completer1->setModel(listModel1);
    completer1->setCompletionMode(QCompleter::PopupCompletion);
    comId->setCompleter(completer1);

    QCompleter *completer2 = new QCompleter(commodity);
    completer2->setCaseSensitivity(Qt::CaseInsensitive);
    QStringListModel *listModel2 = new QStringListModel(completer2);
    listModel2->setStringList(commodities);
    completer2->setModel(listModel2);
    completer2->setCompletionMode(QCompleter::PopupCompletion);
    commodity->setCompleter(completer2);

    comIds[0] = "";
    commodities[0] = "";

    comId->addItems(comIds);
    commodity->addItems(commodities);
    clearItems();
    table->setList(tableValues);
    table->showRow(table->rowCount() - 1);
    for(int i=0; i< table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width - 60)/table->columnCount());
    }
    int tot = table->getSumOfColumn(5) + MARGIN;
    setGrandTotal("&nbsp;&nbsp;<font size=6><b><center>" + QString::number(tot) + "<br><b><font size=5>&nbsp;" + Commons::numberToWords(tot) + "</b></font>");
    comId->setFocus();
}

void OldPurchaseInvoiceWidget::setDate(QDate date)
{
    invoiceDate = date;
}

void OldPurchaseInvoiceWidget::setInvoiceNo(int inNo)
{
    currentInvoiceNo = QString::number(inNo);
    setData();
}

void OldPurchaseInvoiceWidget::checkId(QString text)
{
    if(text == "")
    {
        return;
    }
    int ind = -1;
    for(int i=0; i< ids.size(); i++)
    {
        if(ids.at(i) == text)
            ind = i;
    }
    if( ind < 0)
    {
        return;
    }
    QStringList data = values.at(ind).split("\n");
    address->setText(data.at(2));
    phoneNo->setText(data.at(3));
    mobile->setText(data.at(4));
    email->setText(data.at(6));
}

void OldPurchaseInvoiceWidget::checkCode(QString text)
{
    if(text == "")
    {
        return;
    }
    int ind = -1;
    for(int i=0; i< comIds.size(); i++)
    {
        if(comIds.at(i) == text)
            ind = i;
    }
    if( ind < 0)
    {
        return;
    }
    QStringList data = comValues.at(ind-1).split("\n");
    commodity->setCurrentIndex(ind);
    tax->setText(data.at(2));
    price->setText(data.at(3));
}

void OldPurchaseInvoiceWidget::clearCustomerData()
{
    name->setText("");
    address->setText("");
    phoneNo->setText("");
    mobile->setText("");
    email->setText("");
}

void OldPurchaseInvoiceWidget::clearItems()
{
    comId->setCurrentIndex(0);
    commodity->setCurrentIndex(0);
    quantity->setText("1");
    tax->setText("");
    price->setText("");
}

void OldPurchaseInvoiceWidget::addAnItem()
{
    try
    {
        QString id = comId->currentText();
        QString nme = commodity->currentText();
        if( id == "" || nme == "")
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Invalid Addition");
            msgBox.setText("Commodity Id or Name is empty!!");
            msgBox.exec();
            return;
        }
        DatabaseServer server;
        QString available = server.getSingleResult("select Quantity from Commodity where Id='" + comId->currentText() + "'");

        QString tx = QString::number(tax->text().toFloat());
        QString unit = QString::number(price->text().toFloat(), 'f', 2);
        QString qty = QString::number(quantity->text().toFloat());
        float gross = qty.toFloat() * unit.toFloat();
        float taxAmt = gross * tx.toFloat() / 100;
        QString total = QString::number(qty.toFloat() * unit.toFloat() + taxAmt, 'f', 2);
        tableValues.append(id + "\n" + nme + "\n" + tx + "\n" + unit + "\n" + qty + "\n" + QString::number(gross) + "\n" + QString::number(taxAmt) + "\n" + total);
        table->setList(tableValues);

        clearItems();
        int tot = table->getSumOfColumn(5) + MARGIN;
        setGrandTotal("&nbsp;&nbsp;<font size=6><b><center>" + QString::number(tot) + "<br><b><font size=5>&nbsp;" + Commons::numberToWords(tot) + "</b></font>");
        comId->setFocus();
    }
    catch(...)
    {
        qDebug()<<"Some execeptions here!!";
    }
}

void OldPurchaseInvoiceWidget::removeItem()
{
    GetSerialNoDialog dialog;
    int serialNo = dialog.getSerialNo().toInt();
    if(serialNo > 0 && serialNo < tableValues.size())
    {
        tableValues.removeAt(serialNo);
        table->setList(tableValues);
        clearItems();
        int tot = table->getSumOfColumn(5) + MARGIN;
        setGrandTotal("&nbsp;&nbsp;<font size=6><b><center>" + QString::number(tot) + "<br><b><font size=5>&nbsp;" + Commons::numberToWords(tot) + "</b></font>");
        comId->setFocus();
    }
    else if(serialNo > 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Serial No");
        msgBox.setText("No item found on this serial number!");
        msgBox.exec();
    }
}

void OldPurchaseInvoiceWidget::removeLastItem()
{
    if(tableValues.size() > 1)
        tableValues.removeLast();
    table->setList(tableValues);
    clearItems();
    int tot = table->getSumOfColumn(5) + MARGIN;
    setGrandTotal("&nbsp;&nbsp;<font size=6><b><center>" + QString::number(tot) + "<br><b><font size=5>&nbsp;" + Commons::numberToWords(tot) + "</b></font>");
    comId->setFocus();
}

bool OldPurchaseInvoiceWidget::printInvoiceHtml(int from)
{
    if(tableValues.size() <= 1)
        return false;

    float total = table->getSumOfColumn(5);
    float gross = 0;
    for( int i = 0;  i < table->rowCount(); i++)
    {
        float unit = table->getItem(i, 3).toFloat();
        float qty = table->getItem(i, 4).toFloat();
        gross += (unit * qty);
    }
    float tx = total - gross;
    float css = 0;
    total += css;

    QStringList invoiceData;
    invoiceData.append(Commons::getInvoiceNo());
    invoiceData.append(invoiceDate.toString("dd-MM-yyyy"));
    QStringList customerDetails;
    customerDetails.append(name->text());
    customerDetails.append(address->text());
    customerDetails.append(mobile->text());
    customerDetails.append(phoneNo->text());
    customerDetails.append(email->text());
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

    QStringList summary;
    summary.append(QString::number(gross));
    summary.append(QString::number(tx));
    summary.append(QString::number(css));
    summary.append(QString::number(total));
    summary.append(Commons::numberToWords((int) total));
    summary.append("");
    summary.append("");
    PrintModule *pm = new PrintModule;
    pm->setPreviewMode(true);
    pm->setNoOfCopies(1);
    pm->setFilename("PurchaseBill.html");
    pm->printBillHtml(invoiceData, customerDetails, tableData, summary);

    return true;
}

void OldPurchaseInvoiceWidget::saveInvoice()
{
    if(tableValues.size() <= 1)
        return;

    DatabaseServer *server = new DatabaseServer;
    // Cancel Invoice
    QStringList data = server->getMultiListResult("select CommodityId, Quantity from StockInvoice where InvoiceNo=" + currentInvoiceNo);
    for(int i = 0; i < data.size(); i++)
    {
        QStringList values = data.at(i).split("\n");
        server->executeQuery("update Commodity set Quantity = Quantity - " + values.at(1) + ", LastUpdate = '" + invoiceDate.toString("yyyy-MM-dd") + "' where Id = '" + values.at(0) + "'");
    }
    delete server;

    TableStockInvoice::deleteInvoice(currentInvoiceNo);

    int customerId = TableCustomers::addNewCustomer(name->text(), address->text(), phoneNo->text(), mobile->text(), email->text());

    for(int i = 0; i < table->rowCount(); i++)
    {
        server = new DatabaseServer;
        server->executeQuery("update Commodity set Quantity=Quantity+" + table->getItem(i, 4) + ", LastUpdate = '" + invoiceDate.toString("yyyy-MM-dd") + "' where Id='" + table->getItem(i,0) + "'");
        delete server;
        TableStockInvoice::addNewEntry(currentInvoiceNo, QString::number(customerId), table->getItem(i, 0), table->getItem(i, 1), table->getItem(i, 2), table->getItem(i, 3), table->getItem(i, 4), table->getItem(i, 7), invoiceDate);
    }
}

void OldPurchaseInvoiceWidget::printAndSave()
{
    if(!printInvoiceHtml(1))
        return;
    saveInvoice();
    setData();
}

void OldPurchaseInvoiceWidget::saveOnly()
{
    saveInvoice();
    QMessageBox msgBox;
    msgBox.setText("Invoice Saved Successfully!");
    msgBox.exec();
}

void OldPurchaseInvoiceWidget::totalCorrection(QString total)
{
    float nTotal = total.toFloat();
    float nTax = tax->text().toFloat();

    float nGross = (100 * nTotal) / (100 + nTax);

    price->setText(QString::number(nGross));
}
