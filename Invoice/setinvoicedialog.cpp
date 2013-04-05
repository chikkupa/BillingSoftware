#include "setinvoicedialog.h"
#include <QtGui>
#include "databaseserver.h"

setInvoiceDialog::setInvoiceDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Set Invoice- Dialog");
    resize(600,300);

    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QRegExp regExp("[1-9][0-9]*");
    QLabel *label1 = new QLabel("<b>New Invoice No: <b>");
    label1->setMinimumWidth(200);
    invoiceNo = new QLineEdit;
    invoiceNo->setValidator(new QRegExpValidator(regExp, this));
    QPushButton *ok = new QPushButton("Ok");
    QPushButton *cancel = new QPushButton("Cancel");

    hlay1->addWidget(label1);
    hlay1->addWidget(invoiceNo);

    hlay2->addStretch();
    hlay2->addWidget(ok);
    hlay2->addWidget(cancel);

    mainLayout->addStretch();
    mainLayout->addLayout(hlay1);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay2);

    setAttribute(Qt::WA_QuitOnClose);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

void setInvoiceDialog::setInvoiceNo()
{
    if(exec())
    {
        DatabaseServer server;

        if(invoiceNo->text() == "")
            return setInvoiceNo();
        server.executeQuery("update Details set Value='" + invoiceNo->text() + "' where Field='Invoice'");
    }
}
