#include "invoicewidget.h"
#include <QtGui>
#include "databaseserver.h"
#include "commons.h"
#include "getserialnodialog.h"
#include "tableinvoice.h"
#include "tablecustomers.h"
#include "printmodule.h"
#include "chellaninvoicedialog.h"
#include "tableconfiguration.h"

#define MARGIN 0.00 // Margin for round off

InvoiceWidget::InvoiceWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4, *hlay5, *hlay6, *hlay7, *hlay8, *hlay9, *hlay10, *hlay11, *hlay12;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *vlay1, *vlay2, *vlay3, *vlay4, *vlay5, *vlay6, *vlay7, *vlay8, *vlay9;

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
    hlay12 = new QHBoxLayout;

    vlay1 = new QVBoxLayout;
    vlay2 = new QVBoxLayout;
    vlay3 = new QVBoxLayout;
    vlay4 = new QVBoxLayout;
    vlay5 = new QVBoxLayout;
    vlay6 = new QVBoxLayout;
    vlay7 = new QVBoxLayout;
    vlay8 = new QVBoxLayout;
    vlay9 = new QVBoxLayout;

    QLabel *header = new QLabel;
    QDateEdit *dateEdit = new QDateEdit;
    dateEdit->setDate(QDate::currentDate());
    invoiceDate = QDate::currentDate();
    noPrints = new QSpinBox;
    noPrints->setRange(0, 10);
    noPrints->setValue(1);

    QLabel *customerHead = new QLabel("<b><center>Customer Details</center></b>");
    QLabel *label2 = new QLabel("Name: ");
    QLabel *label3 = new QLabel("Address: ");
    QLabel *label4 = new QLabel("Telephone: ");
    QLabel *label5 = new QLabel("Mobile: ");
    QLabel *label7 = new QLabel("Email: ");
    QLabel *label8 = new QLabel("No of Prints: ");

    QLabel *commodityHead = new QLabel("<center><b>Item Details</b><center>");
    QLabel *label11 = new QLabel("Item Code: ");
    QLabel *label12 = new QLabel("Item Name: ");
    QLabel *label13 = new QLabel("Quantity: ");
    QLabel *label14 = new QLabel("Tax: ");
    QLabel *label15 = new QLabel("Rate: ");
    QLabel *label16 = new QLabel("Total: ");
    QLabel *label17 = new QLabel("Discount: ");

    QLabel *label21 = new QLabel("<b>Date: </b>");
    QLabel *label22 = new QLabel("<b>RETAIL INVOICE</b>");
    QLabel *label23 = new QLabel("Payment: ");

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
    discount = new QLineEdit;
    discount->setValidator(new QRegExpValidator(regExp, this));
    total->setValidator(new QRegExpValidator(regExp, this));

    QPushButton *addItem = new QPushButton("Add Item");
    addItem->setDefault(true);
    addItem->setShortcut(QKeySequence(tr("Ctrl+Space")));
    addItem->setToolTip("Shortcut: Ctrl + Space");
    QPushButton *returnItem = new QPushButton("Return Item");
    if(TableConfiguration::getReturnItemStatus())
        returnItem->show();
    else
        returnItem->hide();
    QPushButton *removeItem = new QPushButton("Remove Item");
    removeItem->setShortcut(QKeySequence(tr("Ctrl+Alt+Space")));
    removeItem->setToolTip("Shortcut: Ctrl + Alt + Space");
    QPushButton *removeLast = new QPushButton(this);
    removeLast->setMaximumWidth(0);
    removeLast->setShortcut(QKeySequence(tr("Ctrl+Shift+Space")));
    table = new ListTableWidget;

    QPushButton *print = new QPushButton("Print and Save");
    print->setMaximumWidth(150);
    print->setShortcut(QKeySequence(tr("Ctrl+S")));
    print->setToolTip("Shortcut: Ctrl + S");
    QPushButton *printOnly = new QPushButton("Print Only");
    printOnly->setMaximumWidth(150);
    printOnly->setShortcut(QKeySequence(tr("Ctrl+P")));
    printOnly->setToolTip("Shortcut: Ctrl + P");
    printOnly->hide();
    QPushButton *save = new QPushButton("Save");
    save->setMaximumWidth(150);
    QPushButton *chellanInvoice = new QPushButton("Get Chellan Cum Invoice");
    chellanInvoice->hide();
    QLabel *grandTotal = new QLabel;
    payment = new QLineEdit;
    quantity->setValidator(new QRegExpValidator(regExp, this));
    QLabel *balance = new QLabel;
    balance->setMinimumWidth(150);

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

    vlay2->addWidget(label11);
    vlay2->addWidget(comId);
    vlay3->addWidget(label12);
    vlay3->addWidget(commodity);
    vlay4->addWidget(label13);
    vlay4->addWidget(quantity);;
    vlay5->addWidget(label14);
    vlay5->addWidget(tax);
    vlay6->addWidget(label15);
    vlay6->addWidget(price);
    vlay7->addWidget(label16);
    vlay7->addWidget(total);
    hlay11->addWidget(returnItem);
    hlay11->addStretch();
    hlay12->addWidget(addItem);
    hlay12->addWidget(removeItem);
    vlay8->addLayout(hlay11);
    vlay8->addLayout(hlay12);
    vlay9->addWidget(label17);
    vlay9->addWidget(discount);

    hlay4->addLayout(vlay2);
    hlay4->addLayout(vlay3);
    hlay4->addLayout(vlay4);
    hlay4->addLayout(vlay5);
    hlay4->addLayout(vlay6);
    hlay4->addLayout(vlay9);
    hlay4->addLayout(vlay7);
    hlay4->addLayout(vlay8);

    hlay6->addWidget(commodityHead);
    hlay7->addWidget(print);
    hlay7->addWidget(printOnly);
    hlay7->addWidget(save);
    hlay7->addStretch();
    hlay7->addWidget(chellanInvoice);
    vlay1->addLayout(hlay7);
    hlay9->addLayout(vlay1, 1);
    hlay9->addWidget(grandTotal, 2);
    hlay9->addWidget(label23);
    hlay9->addWidget(payment);
    hlay9->addWidget(balance);
    hlay10->addWidget(label21);
    hlay10->addWidget(dateEdit);
    hlay10->addStretch();
    hlay10->addWidget(label22);
    hlay10->addStretch();
    hlay10->addWidget(label8);
    hlay10->addWidget(noPrints);

    mainLayout->addWidget(header);
    mainLayout->addLayout(hlay10);
    mainLayout->addLayout(hlay3);
    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);
    mainLayout->addLayout(hlay6);
    mainLayout->addLayout(hlay4);
    mainLayout->addLayout(hlay5);
    mainLayout->addWidget(table);
    mainLayout->addLayout(hlay9);

    connect( dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setDate(QDate)));
    connect( comId, SIGNAL(currentIndexChanged(QString)), this, SLOT(checkCode(QString)));
    connect( commodity, SIGNAL(currentIndexChanged(int)), comId, SLOT(setCurrentIndex(int)));
    connect( addItem, SIGNAL(clicked()), this, SLOT(addAnItem()));
    connect( returnItem, SIGNAL(clicked()), this, SLOT(returnItem()));
    connect( removeItem, SIGNAL(clicked()), this, SLOT(removeItem()));
    connect( removeLast,SIGNAL(clicked()), this, SLOT(removeLastItem()));
    connect( this, SIGNAL(setGrandTotal(QString)), grandTotal, SLOT(setText(QString)));
    connect( print, SIGNAL(clicked()), this, SLOT(printAndSave()));
    connect( printOnly, SIGNAL(clicked()), this, SLOT(printInvoiceHtml()));
    connect( chellanInvoice, SIGNAL(clicked()), this, SLOT(getChellanInvoiceDialog()));
    connect( save, SIGNAL(clicked()), this, SLOT(saveOnly()));
    connect( this, SIGNAL(setHeader(QString)), header, SLOT(setText(QString)));
    connect( total, SIGNAL(textChanged(QString)), this, SLOT(totalCorrection(QString)));
    connect( addItem, SIGNAL(clicked()), total, SLOT(clear()));
    connect( payment, SIGNAL(textChanged(QString)), this, SLOT(getBalance()));
    connect( this, SIGNAL(setBalance(QString)), balance, SLOT(setText(QString)));
}

void InvoiceWidget::setData()
{
    clearDealerData();
    Commons::setNextInvoice();
    setHeader(Commons::getHeaderFromTable());
    DatabaseServer server;

    comIds.clear();
    commodities.clear();
    comIds += "";
    commodities += "";
    comIds += server.getListResult("select Id from Commodity");
    commodities += server.getListResult("select Name from Commodity");
    comValues = server.getMultiListResult("select Id,Name,Tax,Price,Cess from Commodity");
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

    comId->addItems(comIds);
    commodity->addItems(commodities);
    clearItems();
    tableValues.clear();
    tableValues.append("Item Code\nItem Name\nTax\nUnit Price\nQty\nDiscount\nTaxable\nTax Amt\nTotal");
    table->setList(tableValues);
    table->setSortingEnabled(false);
    table->showRow(table->rowCount() - 1);
    for(int i=0; i< table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width - 60)/table->columnCount());
    }
    setGrandTotal("");
}

void InvoiceWidget::setDate(QDate date)
{
    invoiceDate = date;
}

void InvoiceWidget::checkId(QString text)
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

void InvoiceWidget::checkCode(QString text)
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

void InvoiceWidget::clearDealerData()
{
    name->setText("");
    address->setText("");
    phoneNo->setText("");
    mobile->setText("");
    email->setText("");
}

void InvoiceWidget::clearItems()
{
    comId->setCurrentIndex(0);
    commodity->setCurrentIndex(0);
    quantity->setText("1");
    tax->clear();
    price->setText("");
    discount->setText("0");
    payment->setText("");
    setBalance("");
}

void InvoiceWidget::addAnItem()
{
    QString id = comId->currentText();
    QString name = commodity->currentText();
    if( id == "" || name == "")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Addition");
        msgBox.setText("Commodity Id or Name is empty!!");
        msgBox.exec();
        return;
    }
    bool stockStatus = TableConfiguration::getCheckStockStatus();
    DatabaseServer server;
    QString available = server.getSingleResult("select Quantity from Commodity where Id='" + comId->currentText() + "'");
    float totalQty = getPrevouslyAddedQty(comId->currentText()) + quantity->text().toFloat();
    if(!stockStatus)
        available = QString::number(totalQty + 1);
    if(totalQty > available.toFloat())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Addition");
        msgBox.setText("Insufficient quantity of item!");
        msgBox.exec();
        return;
    }
    QString tx = QString::number(tax->text().toFloat(), 'f', 2);
    QString unit = QString::number(price->text().toFloat(), 'f', 2);
    QString qty = QString::number(quantity->text().toFloat(), 'f', 2);
    QString discount = QString::number(this->discount->text().toFloat());
    float disc = 100 * discount.toFloat() / (100 + tax->text().toFloat());
    float fTax = tax->text().toFloat();
    float fUnit = price->text().toFloat();
    float fQty = quantity->text().toFloat();
    discount = QString::number(disc, 'f', 2);
    float gross = (fQty * fUnit - disc);
    float taxAmt = gross * fTax / 100;
    QString total = QString::number(gross + taxAmt, 'f', 2);
    tableValues.append(id + "\n" + name + "\n" + tx + "\n" + unit + "\n" + qty + "\n"+ discount + "\n" + QString::number(gross, 'f', 2) + "\n" + QString::number(taxAmt, 'f', 2) + "\n" + total);
    table->setList(tableValues);
    table->setSortingEnabled(false);
    clearItems();
    float tot = table->getSumOfColumn(8) + MARGIN;
    setGrandTotal("&nbsp;&nbsp;<font size=6><b><center>" + QString::number(tot) + "<br><b><font size=5>&nbsp;" + Commons::numberToWords(tot) + "</b></font>");
    comId->setFocus();
}

float InvoiceWidget::getPrevouslyAddedQty(QString commodityId)
{
    float quantity = 0;
    for(int i = 0; i < table->rowCount(); i++)
    {
        if(table->getItem(i, 0) == commodityId)
        {
            quantity += table->getItem(i, 4).toFloat();
        }
    }
    return quantity;
}

void InvoiceWidget::returnItem()
{
    QString id = comId->currentText();
    QString name = commodity->currentText();
    if( id == "" || name == "")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Addition");
        msgBox.setText("Commodity Id or Name is empty!!");
        msgBox.exec();
        return;
    }

    QString tx = QString::number(tax->text().toFloat(), 'f', 2);
    QString unit = QString::number(price->text().toFloat(), 'f', 2);
    QString qty = QString::number(quantity->text().toFloat() * -1);
    QString discount = QString::number(this->discount->text().toFloat(), 'f', 2);
    float disc = 100 * discount.toFloat() / (100 + tax->text().toFloat());
    discount = QString::number(disc, 'f', 2);
    float fTax = tax->text().toFloat();
    float fUnit = price->text().toFloat();
    float fQty = quantity->text().toFloat() * -1;
    discount = QString::number(disc, 'f', 2);
    float gross = (fQty * fUnit + disc);
    float taxAmt = gross * fTax / 100;
    QString total = QString::number(gross + taxAmt, 'f', 2);
    tableValues.append(id + "\n" + name + "\n" + tx + "\n" + unit + "\n" + qty + "\n"+ discount + "\n" + QString::number(gross) + "\n" + QString::number(taxAmt) + "\n" + total);
    table->setList(tableValues);
    table->setSortingEnabled(false);
    clearItems();
    float tot = table->getSumOfColumn(8) - MARGIN;
    setGrandTotal("&nbsp;&nbsp;<font size=6><b><center>" + QString::number(tot) + "<br><b><font size=5>&nbsp;" + Commons::numberToWords(tot) + "</b></font>");
    comId->setFocus();
}

void InvoiceWidget::removeItem()
{
    GetSerialNoDialog dialog;
    int serialNo = dialog.getSerialNo().toInt();
    if(serialNo > 0 && serialNo < tableValues.size())
    {
        tableValues.removeAt(serialNo);
        //table->setList(tableValues);
        //table->setSortingEnabled(false);
        table->removeRow(serialNo - 1);
        tableValues.clear();
        tableValues.append("Item Code\nItem Name\nTax\nUnit Price\nQty\nDiscount\nTaxable\nTax Amt\nTotal");
        for(int i = 0; i < table->rowCount(); i++)
        {
            QString row = table->getItem(i, 0);
            for(int j = 1; j < table->columnCount(); j++)
                row += "\n" + table->getItem(i, j);
            tableValues.append(row);
        }
        clearItems();
        float tot = table->getSumOfColumn(8) + MARGIN;
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

void InvoiceWidget::removeLastItem()
{
    if(tableValues.size() > 1)
        tableValues.removeLast();
    table->setList(tableValues);
    table->setSortingEnabled(false);
    clearItems();
    int tot = table->getSumOfColumn(8) + MARGIN;
    setGrandTotal("&nbsp;&nbsp;<font size=6><b><center>" + QString::number(tot) + "<br><b><font size=5>&nbsp;" + Commons::numberToWords(tot) + "</b></font>");
    comId->setFocus();
}

bool InvoiceWidget::printInvoiceHtml(int from)
{
    if(tableValues.size() <= 1)
        return false;

    float total = table->getSumOfColumn(8);
    float gross = 0;
    for( int i = 0;  i < table->rowCount(); i++)
    {
        float unit = table->getItem(i, 3).toFloat();
        float qty = table->getItem(i, 4).toFloat();
        float disc = table->getItem(i, 5).toFloat();
        gross += (unit * qty - disc);
    }
    float tx = total - gross;
    float css = 0;
    total += css;
    float payment = this->payment->text().toFloat();
    float balance = payment - total;

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
    summary.append(QString::number(payment));
    summary.append(QString::number(balance));
    PrintModule *pm = new PrintModule;
    pm->setPreviewMode(true);
    pm->setNoOfCopies(noPrints->text().toInt());
    pm->printBillHtml(invoiceData, customerDetails, tableData, summary);

    return true;
}

void InvoiceWidget::getChellanInvoiceDialog()
{
    ChellanInvoiceDialog dialog;
    QStringList address;
    address.append(name->text());
    address.append(this->address->text());
    QStringList chellanDetails = dialog.getChellanInvoiceDetails(address, Commons::getInvoiceNo());
    if(chellanDetails.size() > 0)
    {
        if(tableValues.size() <= 1)
            return;

        QStringList invoiceData;
        invoiceData.append(Commons::getInvoiceNo());
        invoiceData.append(invoiceDate.toString("dd-MM-yyyy"));
        QStringList customerDetails;
        customerDetails.append(name->text());
        QStringList tableData;
        tableData.append("Item Code\nItem\nTax\nPrice\nQuantity\nTotal");
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
        float total = table->getSumOfColumn(5);
        float tx = table->getItem(0,2).toFloat() * total /100;
        float gross = total - tx;
        float css = tx /100;
        float payment = this->payment->text().toFloat();
        float balance = payment - balance;
        QStringList summary;
        summary.append(QString::number(gross));
        summary.append(QString::number(tx));
        summary.append(QString::number(css));
        summary.append(QString::number(total));
        summary.append(Commons::numberToWords((int) total));
        summary.append(QString::number(payment));
        summary.append(QString::number(balance));
        PrintModule pm;
        pm.setPreviewMode(false);
        pm.setNoOfCopies(1);
        pm.printChellanHtml(invoiceData, customerDetails, tableData, summary, chellanDetails);
        saveInvoice();
        setData();
    }
}

void InvoiceWidget::saveInvoice()
{
    if(tableValues.size() <= 1)
        return;

    qDebug()<< "[Savenvoice]: More than one table values.......";
    DatabaseServer *server = new DatabaseServer;
    QString invoice = server->getSingleResult("select Value from Details where Field='Invoice'");
    // Cancel Invoice
    QStringList data = server->getMultiListResult("select CommodityId, Quantity from Invoice where InvoiceNo=" + invoice);
    for(int i = 0; i < data.size(); i++)
    {
        QStringList values = data.at(i).split("\n");
        server->executeQuery("update Commodity set Quantity = Quantity + " + values.at(1) + " where Id = '" + values.at(0) + "'");
    }
    delete server;

    TableInvoice::deleteInvoice(invoice);

    int customerId = TableCustomers::addNewCustomer(name->text(), address->text(), phoneNo->text(), mobile->text(), email->text());

    for(int i = 0; i < table->rowCount(); i++)
    {
        server = new DatabaseServer;
        server->executeQuery("update Commodity set Quantity=Quantity-" + table->getItem(i, 4) + " where Id='" + table->getItem(i,0) + "'");
        delete server;
        TableInvoice::addNewEntry(invoice, QString::number(customerId), table->getItem(i, 0), table->getItem(i, 1), table->getItem(i, 2), table->getItem(i, 3), table->getItem(i, 4), table->getItem(i, 5), table->getItem(i, 8), invoiceDate);
    }
}

void InvoiceWidget::printAndSave()
{
    if(!printInvoiceHtml(1))
        return;
    qDebug()<< "[printAndSave]: More than one table values.......";
    saveInvoice();
    setData();
}

void InvoiceWidget::saveOnly()
{
    saveInvoice();
    QMessageBox msgBox;
    msgBox.setText("Invoice Saved Successfully!");
    msgBox.exec();
}

void InvoiceWidget::getBalance()
{
    float total = table->getSumOfColumn(8);
    float balance = this->payment->text().toFloat() - total;
    setBalance("<font size=6><b>Balance: " + QString::number(balance) + "</b></font>");
}

void InvoiceWidget::totalCorrection(QString total)
{
    float nTotal = total.toFloat();
    float nTax = tax->text().toFloat();

    float nGross = (100 * nTotal) / (100 + nTax);

    price->setText(QString::number(nGross));
}
