#include "chellaninvoicedialog.h"
#include <QtGui>

ChellanInvoiceDialog::ChellanInvoiceDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Chellan Cum Invoice- Dialog");

    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4, *hlay5, *hlay6, *hlay7, *hlay8, *hlay9, *hlay10, *hlay11, *hlay12;
    QVBoxLayout *vlay1, *vlay2;
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
    hlay11 = new QHBoxLayout;
    hlay12 = new QHBoxLayout;

    vlay1 = new QVBoxLayout;
    vlay2 = new QVBoxLayout;

    QLabel *label1 = new QLabel("Delevery Note: ");
    QLabel *label2 = new QLabel("Mode/Terms of Payment: ");
    QLabel *label3 = new QLabel("Supplier's Reference: ");
    QLabel *label4 = new QLabel("Other References: ");
    QLabel *label5 = new QLabel("Buyer's Order No: ");
    QLabel *label6 = new QLabel("Dated");
    QLabel *label7 = new QLabel("Despatch Document No: ");
    QLabel *label8 = new QLabel("Dated: ");
    QLabel *label9 = new QLabel("Despatch Through: ");
    QLabel *label10 = new QLabel("Destination: ");
    QLabel *label11 = new QLabel("Consignee: ");
    QLabel *label12 = new QLabel("Buyer: ");
    QLabel *label13 = new QLabel("Terms of Delivery: ");

    label1->setMinimumWidth(200);
    label2->setMinimumWidth(200);
    label3->setMinimumWidth(200);
    label4->setMinimumWidth(200);
    label5->setMinimumWidth(200);
    label6->setMinimumWidth(200);
    label7->setMinimumWidth(200);
    label8->setMinimumWidth(200);
    label9->setMinimumWidth(200);
    label10->setMinimumWidth(200);

    deliveryNote = new QLineEdit;
    modeOfPayement = new QLineEdit;
    suppliersRef = new QLineEdit;
    otherRef = new QLineEdit;
    orderNo = new QLineEdit;
    orderDate = new QLineEdit;
    despatchNo = new QLineEdit;
    despatchDate = new QLineEdit;
    despatchThrough = new QLineEdit;
    destination = new QLineEdit;
    consignee = new QTextEdit;
    buyer = new QTextEdit;
    termsOfDelivery = new QTextEdit;
    QPushButton *ok= new QPushButton("Ok");
    ok->setDefault(true);
    QPushButton *cancel= new QPushButton("Cancel");

    hlay1->addWidget(label1);
    hlay1->addWidget(deliveryNote);
    hlay2->addWidget(label2);
    hlay2->addWidget(modeOfPayement);
    hlay3->addWidget(label3);
    hlay3->addWidget(suppliersRef);
    hlay4->addWidget(label4);
    hlay4->addWidget(otherRef);
    hlay5->addWidget(label5);
    hlay5->addWidget(orderNo);
    hlay6->addWidget(label6);
    hlay6->addWidget(orderDate);
    hlay7->addWidget(label7);
    hlay7->addWidget(despatchNo);
    hlay8->addWidget(label8);
    hlay8->addWidget(despatchDate);
    hlay9->addWidget(label9);
    hlay9->addWidget(despatchThrough);
    hlay10->addWidget(label10);
    hlay10->addWidget(destination);
    hlay12->addStretch();
    hlay12->addWidget(cancel);
    hlay12->addWidget(ok);

    vlay1->addWidget(label11);
    vlay1->addWidget(consignee);
    vlay1->addWidget(label12);
    vlay1->addWidget(buyer);
    vlay1->addWidget(label13);
    vlay1->addWidget(termsOfDelivery);
    vlay2->addLayout(hlay1);
    vlay2->addLayout(hlay2);
    vlay2->addLayout(hlay3);
    vlay2->addLayout(hlay4);
    vlay2->addLayout(hlay5);
    vlay2->addLayout(hlay6);
    vlay2->addLayout(hlay7);
    vlay2->addLayout(hlay8);
    vlay2->addLayout(hlay9);
    vlay2->addLayout(hlay10);

    hlay11->addLayout(vlay1);
    hlay11->addStretch();
    hlay11->addLayout(vlay2);
    mainLayout->addLayout(hlay11);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay12);

    setAttribute(Qt::WA_QuitOnClose);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

QStringList ChellanInvoiceDialog::getChellanInvoiceDetails(QStringList address, QString invoiceNo)
{
    consignee->setPlainText(address.at(0) + "\n" + address.at(1));
    suppliersRef->setText(invoiceNo);

    QStringList details;
    if(exec())
    {
        details.append(deliveryNote->text());
        details.append(modeOfPayement->text());
        details.append(suppliersRef->text());
        details.append(otherRef->text());
        details.append(orderNo->text());
        details.append(orderDate->text());
        details.append(despatchNo->text());
        details.append(despatchDate->text());
        details.append(despatchThrough->text());
        details.append(destination->text());
        details.append(consignee->toPlainText().replace("\n", "<br>"));
        details.append(buyer->toPlainText().replace("\n", "<br>"));
        details.append(termsOfDelivery->toPlainText().replace("\n", "<br>"));
    }

    return details;
}
