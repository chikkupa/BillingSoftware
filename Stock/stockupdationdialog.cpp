#include "stockupdationdialog.h"
#include <QtGui>
#include "databaseserver.h"

StockUpdationDialog::StockUpdationDialog(QWidget *parent) :
    QDialog(parent)
{
    status = true;
    setWindowTitle("Stock Addition- Dialog");
    resize(600,300);
    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4;
    QVBoxLayout *mainLayout;

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;
    hlay3 = new QHBoxLayout;
    hlay4 = new QHBoxLayout;
    mainLayout = new QVBoxLayout(this);

    QLabel *label1 = new QLabel("Item Code: ");
    code = new QComboBox;
    QLabel *description = new QLabel;
    QLabel *label2 = new QLabel("Add Stock of: ");
    stock = new QLineEdit;
    QRegExp regExp("[1-9][0-9]*");
    stock->setValidator(new QRegExpValidator(regExp, this));

    ok = new QPushButton("Ok");
    QPushButton *cancel = new QPushButton("Cancel");

    hlay1->addWidget(label1);
    hlay1->addWidget(code);
    hlay2->addWidget(description);
    hlay3->addStretch();
    hlay3->addWidget(ok);
    hlay3->addWidget(cancel);
    hlay4->addWidget(label2);
    hlay4->addWidget(stock);
    mainLayout->addLayout(hlay1);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay2);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay4);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay3);

    setAttribute(Qt::WA_QuitOnClose);

    connect(code, SIGNAL(currentIndexChanged(QString)), this, SLOT(checkId(QString)));
    connect(this, SIGNAL(setDescription(QString)), description, SLOT(setText(QString)));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

bool StockUpdationDialog::stockAddition()
{
    DatabaseServer server;
    ids = server.getListResult("select Id from Commodity;");
    code->clear();
    values = server.getMultiListResult("select Name, Price, Quantity from Commodity;");
    if(values.size() > 0)
    {
        code->addItems(ids);
        QStringList data = values.at(0).split("\n");
        QString displayString = "<center><b>Item Name: "+ data.at(0);
        displayString += "<br><br>Value: " + data.at(1);
        displayString += "<br><br>Stock Remaining: " + data.at(2) + "</b></center>";
        setDescription(displayString);
    }
    if(exec())
    {
        QString date = QDate::currentDate().toString("yyyy-MM-dd");
        server.executeQuery("update Commodity set Quantity=Quantity+" + stock->text() + ",LastUpdate='" + date + "' where Id ='" + code->currentText() + "';");
        stock->setText("");
        return true;
    }
    return false;
}

void StockUpdationDialog::checkId(QString text)
{
    int ind = -1;
    for(int i=0; i< ids.size(); i++)
    {
        if(ids.at(i) == text)
            ind = i;
    }
    if( ind < 0)
    {
        status = false;
        ok->setEnabled(false);
        setDescription("<center><b><font color=red>Item not found!!</font></b></center>");
        return;
    }
    status =true;
    ok->setEnabled(true);
    QStringList data = values.at(ind).split("\n");
    QString displayString = "<center><b>Item Name: "+ data.at(0);
    displayString += "<br><br>Value: " + data.at(1);
    displayString += "<br><br>Stock Remaining: " + data.at(2) + "</b></center>";
    setDescription(displayString);
}

