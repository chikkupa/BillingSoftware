#include "configurationdialog.h"
#include <QtGui>
#include "commons.h"
#include "databaseserver.h"

ConfigurationDialog::ConfigurationDialog(int wid, QWidget *parent)  :
    QDialog(parent)
{
    width = wid;
    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4, *hlay5, *hlay6, *hlay7, *hlay8, *hlay9, *hlay10;
    QVBoxLayout *vlay1, *vlay2;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

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

    vlay1 = new QVBoxLayout;
    vlay2 = new QVBoxLayout;

    QLabel *label1 = new QLabel("Shop Name: ");
    QLabel *label2 = new QLabel("Address: ");
    QLabel *label3 = new QLabel("Phone No: ");
    QLabel *label4 = new QLabel("Tin No");
    QLabel *label5 = new QLabel("CST Reg No: ");
    QLabel *label6 = new QLabel("Invoice No: ");
    QLabel *label7 = new QLabel("Estimate No: ");
    QLabel *label8 = new QLabel("Purchase No: ");
    QLabel *label9 = new QLabel("Stock Checking ");
    QLabel *label10 = new QLabel("Return Item ");
    QLabel *invoiceHead = new QLabel("<b>Invoice / Estimate Configuration</b>");

    label1->setMinimumWidth(100);
    label2->setMinimumWidth(100);
    label3->setMinimumWidth(100);
    label4->setMinimumWidth(100);
    label5->setMinimumWidth(100);
    label6->setMinimumWidth(100);
    label7->setMinimumWidth(100);
    label8->setMinimumWidth(100);
    label9->setMinimumWidth(100);

    shopName = new QLineEdit;
    address = new QTextEdit;
    address->setMaximumHeight(200);
    phoneNo = new QLineEdit;
    tinNo = new QLineEdit;
    cstReg = new QLineEdit;
    QRegExp regExp("[0-9]*");
    invoiceNo = new QLineEdit;
    invoiceNo->setValidator(new QRegExpValidator(regExp, this));
    estimateNo = new QLineEdit;
    estimateNo->setValidator(new QRegExpValidator(regExp, this));
    purchaseNo = new QLineEdit;
    purchaseNo->setValidator(new QRegExpValidator(regExp, this));
    stockCheck = new QCheckBox;
    returnItem = new QCheckBox;
    QPushButton *save = new QPushButton("Save Configuration");
    save->setMaximumWidth(200);

    hlay1->addWidget(label1);
    hlay1->addWidget(shopName);
    hlay2->addWidget(label2);
    hlay2->addWidget(address);
    hlay3->addWidget(label3);
    hlay3->addWidget(phoneNo);
    hlay4->addWidget(label4);
    hlay4->addWidget(tinNo);
    hlay5->addWidget(label5);
    hlay5->addWidget(cstReg);
    hlay6->addWidget(label6);
    hlay6->addWidget(invoiceNo);
    hlay7->addWidget(label7);
    hlay7->addWidget(estimateNo);
    hlay9->addWidget(label8);
    hlay9->addWidget(purchaseNo);
    hlay8->addStretch();
    hlay8->addWidget(save);
    hlay8->addStretch();
    hlay10->addWidget(stockCheck);
    hlay10->addWidget(label9);
    hlay10->addStretch();
    hlay10->addWidget(returnItem);
    hlay10->addWidget(label10);
    hlay10->addStretch();

    vlay1->addLayout(hlay1);
    vlay1->addLayout(hlay3);
    vlay1->addLayout(hlay5);
    vlay1->addLayout(hlay7);
    vlay2->addLayout(hlay2);
    vlay2->addLayout(hlay4);
    vlay1->addLayout(hlay6);
    vlay1->addLayout(hlay9);

    hlayout->addStretch();
    hlayout->addLayout(vlay1);
    hlayout->addStretch();
    hlayout->addLayout(vlay2);
    hlayout->addStretch();
    mainLayout->addLayout(hlayout);
    mainLayout->addStretch();
    mainLayout->addWidget(invoiceHead);
    mainLayout->addLayout(hlay10);
    mainLayout->addLayout(hlay8);
    mainLayout->addStretch();

    connect(save, SIGNAL(clicked()), this, SLOT(saveData()));
}

void ConfigurationDialog::getConfiguration()
{
    DatabaseServer *server = new DatabaseServer;
    shopName->setText(server->getSingleResult("select Value from Details where Field='Name'"));
    address->setText(server->getSingleResult("select Value from Details where Field='Address'"));
    phoneNo->setText(server->getSingleResult("select Value from Details where Field='Mobile'"));
    tinNo->setText(server->getSingleResult("select Value from Details where Field='Tin'"));
    cstReg->setText(server->getSingleResult("select Value from Details where Field='CSTRegNo'"));
    invoiceNo->setText(server->getSingleResult("select Value from Details where Field='Invoice'"));
    estimateNo->setText(server->getSingleResult("select Value from Details where Field='Estimate'"));
    purchaseNo->setText(server->getSingleResult("select Value from Details where Field='StockInvoice'"));
    int checkStockStatus = server->getSingleResult("select Value from Details where Field='StockCheck'").toInt();
    if(checkStockStatus)
        stockCheck->setChecked(true);
    else
        stockCheck->setChecked(false);
    int returnitemStatus = server->getSingleResult("select Value from Configuration where Field='ReturnItem'").toInt();
    if(returnitemStatus)
        returnItem->setChecked(true);
    else
        returnItem->setChecked(false);

    delete server;
    if(exec())
        return;
}

void ConfigurationDialog::saveData()
{
    DatabaseServer *server = new DatabaseServer;
    server->executeQuery("update Details set Value='" + shopName->text() + "' where Field='Name'");
    server->executeQuery("update Details set Value='" + address->toPlainText() + "' where Field='Address'");
    server->executeQuery("update Details set Value='" + phoneNo->text() + "' where Field='Mobile'");
    server->executeQuery("update Details set Value='" + tinNo->text() + "' where Field='Tin'");
    server->executeQuery("update Details set Value='" + cstReg->text() + "' where Field='CSTRegNo'");
    server->executeQuery("update Details set Value='" + invoiceNo->text() + "' where Field='Invoice'");
    server->executeQuery("update Details set Value='" + estimateNo->text() + "' where Field='Estimate'");
    server->executeQuery("update Details set Value='" + purchaseNo->text() + "' where Field='StockInvoice'");
    QString checkStockStatus = (stockCheck->isChecked()? "1" : "0");
    server->executeQuery("update Details set Value='" + checkStockStatus + "' where Field='StockCheck'");
    QString returnItemStatus = (returnItem->isChecked()? "1" : "0");
    server->executeQuery("update Configuration set Value='" + returnItemStatus + "' where Field='ReturnItem'");
    delete server;
    accept();
}
