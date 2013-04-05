#include "deletestockdialog.h"
#include <QtGui>
#include "databaseserver.h"

deleteStockDialog::deleteStockDialog(QWidget *parent) :
    QDialog(parent)
{
    status = true;
    setWindowTitle("Delete Stock- Dialog");
    resize(400,300);
    QHBoxLayout *hlay1, *hlay2, *hlay3;
    QVBoxLayout *mainLayout;

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;
    hlay3 = new QHBoxLayout;
    mainLayout = new QVBoxLayout(this);

    QLabel *label1 = new QLabel("Item Code: ");
    code = new QComboBox;
    description = new QLabel;
    ok = new QPushButton("Ok");
    QPushButton *cancel = new QPushButton("Cancel");

    hlay1->addWidget(label1);
    hlay1->addWidget(code);
    hlay2->addWidget(description);
    hlay3->addStretch();
    hlay3->addWidget(ok);
    hlay3->addWidget(cancel);
    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);
    mainLayout->addLayout(hlay3);

    setAttribute(Qt::WA_QuitOnClose);

    connect(code, SIGNAL(currentIndexChanged(QString)), this, SLOT(checkId(QString)));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

void deleteStockDialog::deleteStock()
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
        description->setText(displayString);
    }
    if(exec())
    {
        QString text="Are you sure want to remove the item from list? Yost will lost all your transcation of this item permenantly.";

        QMessageBox msg("Confirm Delete", text, QMessageBox::
        Critical, QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape, QMessageBox::NoButton);

        if(msg.exec()== QMessageBox::Yes)
        {
            server.executeQuery("delete from Commodity where Id='" +code->currentText() + "';");
        }
    }
}

void deleteStockDialog::checkId(QString text)
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
        description->setText("<center><b><font color=red>Item not found!!</font></b></center>");
        return;
    }
    status =true;
    ok->setEnabled(true);
    QStringList data = values.at(ind).split("\n");
    QString displayString = "<center><b>Item Name: "+ data.at(0);
    displayString += "<br><br>Value: " + data.at(1);
    displayString += "<br><br>Stock Remaining: " + data.at(2) + "</b></center>";
    description->setText(displayString);
}
