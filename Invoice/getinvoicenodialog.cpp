#include "getinvoicenodialog.h"
#include <QtGui>

GetInvoiceNoDialog::GetInvoiceNoDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Get Invoice No Dialog");
    resize(500, 250);

    QHBoxLayout *hlay1, *hlay2;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;

    QLabel *label1 = new QLabel("Invoice No: ");
    invoiceNo = new QLineEdit;
    QPushButton *ok = new QPushButton("Ok");
    QPushButton *cancel = new QPushButton("Cancel");

    hlay1->addWidget(label1);
    hlay1->addWidget(invoiceNo);
    hlay2->addStretch();
    hlay2->addWidget(ok);
    hlay2->addWidget(cancel);

    mainLayout->addLayout(hlay1);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay2);

    setAttribute(Qt::WA_QuitOnClose);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

QString GetInvoiceNoDialog::getInvoiceNo()
{
    if(exec())
        return invoiceNo->text();
    return "";
}
