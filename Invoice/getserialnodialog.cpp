#include "getserialnodialog.h"
#include <QtGui>

GetSerialNoDialog::GetSerialNoDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Get Serial No Dialog");
    resize(500, 250);

    QHBoxLayout *hlay1, *hlay2;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;

    QRegExp regExp("[0-9]*");
    QLabel *label1 = new QLabel("Serial No: ");
    serialNo = new QLineEdit;
    serialNo->setValidator(new QRegExpValidator(regExp, this));
    QPushButton *ok = new QPushButton("Ok");
    QPushButton *cancel = new QPushButton("Cancel");

    hlay1->addWidget(label1);
    hlay1->addWidget(serialNo);
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

QString GetSerialNoDialog::getSerialNo()
{
    if(exec())
        return serialNo->text();
    return "";
}

