#include "deleteDataDialog.h"
#include <QtGui>
#include "databaseserver.h"
#include "commons.h"
#include "messages.h"

DeleteDataDialog::DeleteDataDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Delete Data Dialog");

    QHBoxLayout *hlay1, *hlay2;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;

    QLabel *selectHead = new QLabel("<b>Select the data to delete</b>");
    QLabel *label1 = new QLabel("Accounts");
    QLabel *label2 = new QLabel("Estimate");
    QLabel *label3 = new QLabel("Invoice");
    QLabel *label4 = new QLabel("Stock");


    accounts = new QCheckBox;
    accounts->setChecked(false);
    estimate = new QCheckBox;
    estimate->setChecked(false);
    invoice = new QCheckBox;
    invoice->setChecked(false);
    stock = new QCheckBox;
    stock->setChecked(false);
    QPushButton *closeButton = new QPushButton("Close");
    QPushButton *exportButton = new QPushButton("Clear Data");
    exportButton->setDefault(true);

    hlay1->addStretch();
    hlay1->addWidget(accounts);
    hlay1->addWidget(label1);
    hlay1->addStretch();
    hlay1->addWidget(estimate);
    hlay1->addWidget(label2);
    hlay1->addStretch();
    hlay1->addWidget(invoice);
    hlay1->addWidget(label3);
    hlay1->addStretch();
    hlay1->addWidget(stock);
    hlay1->addWidget(label4);
    hlay1->addStretch();
    hlay2->addStretch();
    hlay2->addWidget(closeButton);
    hlay2->addWidget(exportButton);

    mainLayout->addWidget(selectHead);
    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);

    connect( closeButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect( exportButton, SIGNAL(clicked()), this, SLOT(accept()));
}

void DeleteDataDialog::getDeleteDataDialog()
{
    if(exec())
    {
        if(Messages::confirmMessage("The data will removed permanently.\nAre you sure want to clear the data?", "Confirm Removal"))
        {
            DatabaseServer server;
            if(accounts->isChecked())
                server.executeQuery("delete from Accounts");
            if(estimate->isChecked())
                server.executeQuery("delete from Estimate");
            if(invoice->isChecked())
                server.executeQuery("delete from Invoice");
            if(stock->isChecked())
                server.executeQuery("delete from Commodity");
        }
    }
}
