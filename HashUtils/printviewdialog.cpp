#include "printviewdialog.h"
#include <QtGui>

PrintViewDialog::PrintViewDialog(QWidget *parent) :
    QDialog(parent)
{
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    webView = new QWebView;

    QPushButton *ok= new QPushButton("Print");
    ok->setDefault(true);
    QPushButton *cancel= new QPushButton("Cancel Printing");

    hlay1->addStretch();
    hlay1->addWidget(cancel);
    hlay1->addWidget(ok);


    mainLayout->addWidget(webView);
    mainLayout->addLayout(hlay1);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

bool PrintViewDialog::setwebView(QString htmlContent, QString directory)
{
    QString filename = directory + "Sample.html";
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Error opening Sample.htnl!!";
        return false;
    }

    QTextStream out(&file);
    out<<htmlContent;
    file.close();

    webView->setUrl(QUrl(filename));
    showMaximized();
    if(exec())
        return true;
    return false;
}
