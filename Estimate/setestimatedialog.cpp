#include "setestimatedialog.h"
#include <QtGui>
#include "databaseserver.h"

SetEstimateDialog::SetEstimateDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Set Estimate- Dialog");
    resize(600,300);

    QHBoxLayout *hlay1 = new QHBoxLayout;
    QHBoxLayout *hlay2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QRegExp regExp("[1-9][0-9]*");
    QLabel *label1 = new QLabel("<b>New Estimate No: <b>");
    label1->setMinimumWidth(200);
    estimateNo = new QLineEdit;
    estimateNo->setValidator(new QRegExpValidator(regExp, this));
    QPushButton *ok = new QPushButton("Ok");
    QPushButton *cancel = new QPushButton("Cancel");

    hlay1->addWidget(label1);
    hlay1->addWidget(estimateNo);

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

void SetEstimateDialog::setEstimateNo()
{
    if(exec())
    {
        DatabaseServer server;

        if(estimateNo->text() == "")
            return setEstimateNo();
        server.executeQuery("update Details set Value='" + estimateNo->text() + "' where Field='Estimate'");
    }
}

