#include "cancelestimatedialog.h"
#include <QtGui>
#include "databaseserver.h"
#include "tableestimate.h"
#include "messages.h"

CancelEstimateDialog::CancelEstimateDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Cancel Invoice- Dialog");
    resize(600,400);
    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4;
    QVBoxLayout *mainLayout;

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;
    hlay3 = new QHBoxLayout;
    hlay4 = new QHBoxLayout;
    mainLayout = new QVBoxLayout(this);

    QLabel *label1 = new QLabel("Select Type: ");
    QLabel *label2 = new QLabel("Invoice No: ");
    QLabel *label3 = new QLabel("Invoice in between ");
    QLabel *label4 = new QLabel(" and ");

    typeSingle = new QRadioButton("Sigle");
    typeSingle->setChecked(true);
    typeMultiple = new QRadioButton("Multiple");
    QPushButton *clearAllButton = new QPushButton("Clear All");
    invoiceNo = new QLineEdit;
    invoiceNo1 = new QLineEdit;
    invoiceNo2 = new QLineEdit;
    invoiceNo1->setEnabled(false);
    invoiceNo2->setEnabled(false);
    QPushButton *ok= new QPushButton("Ok");
    QPushButton *cancel= new QPushButton("Cancel");

    hlay1->addWidget(label1);
    hlay1->addWidget(typeSingle);
    hlay1->addWidget(typeMultiple);
    hlay1->addWidget(clearAllButton);
    hlay2->addWidget(label2);
    hlay2->addWidget(invoiceNo);
    hlay3->addWidget(label3);
    hlay3->addWidget(invoiceNo1);
    hlay3->addWidget(label4);
    hlay3->addWidget(invoiceNo2);
    hlay4->addStretch();
    hlay4->addWidget(ok);
    hlay4->addWidget(cancel);

    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);
    mainLayout->addLayout(hlay3);
    mainLayout->addLayout(hlay4);

    connect(typeSingle, SIGNAL(clicked(bool)), this, SLOT(setSingleType(bool)));
    connect(typeMultiple, SIGNAL(clicked(bool)), this, SLOT(setMultiType(bool)));
    connect(clearAllButton, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

void CancelEstimateDialog::cancelInvoice()
{
    if(exec())
    {
        DatabaseServer *server = new DatabaseServer;
        if(typeSingle->isChecked())
        {
            server->executeQuery("delete from Estimate where EstimateNo=" + invoiceNo->text());
        }
        else
        {
            server->executeQuery("delete from Estimate where EstimateNo>=" + invoiceNo1->text() + " and " + "EstimateNo<=" + invoiceNo2->text());
        }
        delete server;
    }
}

void CancelEstimateDialog::setSingleType(bool checked)
{
    if(checked)
    {
        invoiceNo1->setEnabled(false);
        invoiceNo2->setEnabled(false);
        invoiceNo->setEnabled(true);
    }
}

void CancelEstimateDialog::setMultiType(bool checked)
{
    if(checked)
    {
        invoiceNo1->setEnabled(true);
        invoiceNo2->setEnabled(true);
        invoiceNo->setEnabled(false);
    }
}

void CancelEstimateDialog::clearAll()
{
    QString message = "Are you sure want to remove Estimate details?";
    if(Messages::confirmMessage(message, "Confirm Removal"))
    {
        TableEstimate::clearAll();
    }
}

