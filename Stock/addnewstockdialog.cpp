#include "addnewstockdialog.h"
#include <QtGui>
#include <QtSql>
#include "tablecommodity.h"

AddNewStockDialog::AddNewStockDialog(QWidget *parent) :
    QDialog(parent)
{
    status = true;
    setWindowTitle("Add New Stock Dialog");
    resize(500, 350);
    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4, *hlay5, *hlay6, *hlay7, *hlay8, *hlay9;
    QVBoxLayout *mainLayout;

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;
    hlay3 = new QHBoxLayout;
    hlay4 = new QHBoxLayout;
    hlay5 = new QHBoxLayout;
    hlay6 = new QHBoxLayout;
    hlay7 = new QHBoxLayout;
    hlay8 = new QHBoxLayout;
    hlay9 = new QHBoxLayout;
    mainLayout = new QVBoxLayout(this);

    QRegExp regExp("[0-9]*([.][0-9]*)?");
    code = new QLineEdit;
    name = new QLineEdit;
    tax = new QLineEdit;
    tax->setValidator(new QRegExpValidator(regExp, this));
    purchasePrice = new QLineEdit;
    purchasePrice->setValidator(new QRegExpValidator(regExp, this));
    value = new QLineEdit;
    value->setValidator(new QRegExpValidator(regExp, this));
    cess = new QLineEdit;
    cess->setValidator(new QRegExpValidator(regExp, this));
    stock = new QLineEdit;
    stock->setValidator(new QRegExpValidator(regExp, this));
    message = new QLabel;

    QLabel *label1 = new QLabel("Item Code: ");
    QLabel *label2 = new QLabel("Name of the item: ");
    QLabel *label3 = new QLabel("Tax: ");
    QLabel *label4 = new QLabel("Sales Price: ");
    QLabel *label6 = new QLabel("Cess: ");
    QLabel *label5 = new QLabel("Stock Available: ");
    QLabel *label7 = new QLabel("Purchase Price: ");
    ok= new QPushButton("Ok");
    QPushButton *cancel= new QPushButton("Cancel");
    ok->setEnabled(false);
    label1->setMinimumWidth(150);
    label2->setMinimumWidth(150);
    label3->setMinimumWidth(150);
    label4->setMinimumWidth(150);
    label5->setMinimumWidth(150);
    label6->setMinimumWidth(150);
    label7->setMinimumWidth(150);

    hlay1->addWidget(label1);
    hlay1->addWidget(code);
    hlay2->addWidget(label2);
    hlay2->addWidget(name);
    hlay3->addWidget(label3);
    hlay3->addWidget(tax);
    hlay4->addWidget(label4);
    hlay4->addWidget(value);
    hlay5->addWidget(label5);
    hlay5->addWidget(stock);
    hlay6->addStretch();
    hlay6->addWidget(ok);
    hlay6->addWidget(cancel);
    hlay7->addWidget(message);
    hlay8->addWidget(label6);
    hlay8->addWidget(cess);
    hlay9->addWidget(label7);
    hlay9->addWidget(purchasePrice);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);
    mainLayout->addLayout(hlay3);
    mainLayout->addLayout(hlay9);
    mainLayout->addLayout(hlay4);
    mainLayout->addLayout(hlay8);
    mainLayout->addLayout(hlay5);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay7);
    mainLayout->addLayout(hlay6);
    mainLayout->addStretch();

    setAttribute(Qt::WA_QuitOnClose);

    connect(code, SIGNAL(textChanged(QString)), this, SLOT(checkFilled(QString)));
    connect(code, SIGNAL(textChanged(QString)), this, SLOT(checkCode(QString)));
    connect(name, SIGNAL(textChanged(QString)), this, SLOT(checkFilled(QString)));
    connect(tax, SIGNAL(textChanged(QString)), this, SLOT(checkFilled(QString)));
    connect(value, SIGNAL(textChanged(QString)), this, SLOT(checkFilled(QString)));
    connect(stock, SIGNAL(textChanged(QString)), this, SLOT(checkFilled(QString)));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

void AddNewStockDialog::checkFilled(QString val)
{
    if(code->text() != "" && name->text() != "" && tax->text() != "" && value->text() != "" && stock->text() != "" && status)
    {
        ok->setEnabled(true);
        return;
    }
    ok->setEnabled(false);
}

void AddNewStockDialog::checkCode(QString code)
{
    for(int i=0; i < record.size(); i++)
    {
        if(record.at(i) == code)
        {
            message->setText("<font size=3 color=red><center><b>Item Code Not Available!!</b></center></font>");
            status = false;
            checkFilled(code);
            return;
        }
    }
    status = true;
    message->clear();
    checkFilled(code);
}

void AddNewStockDialog::addNewStock()
{
    record = TableCommodity::getCommodityIds();
    if(exec())
    {
        QString date = QDate::currentDate().toString("yyyy-MM-dd");
        float tax = this->tax->text().toFloat();
        float purchasePrice = this->purchasePrice->text().toFloat();
        float price = this->value->text().toFloat();
        float cess = this->cess->text().toFloat();
        float stock = this->stock->text().toFloat();

        QString sTax = QString::number(tax);
        QString sPurchasePrice = QString::number(purchasePrice);
        QString sPrice = QString::number(price);
        QString sCess = QString::number(cess);
        QString sStock = QString::number(stock);
        TableCommodity::addNewItem(code->text(), name->text(), sTax, sPurchasePrice, sPrice, sCess, sStock);
    }
}
