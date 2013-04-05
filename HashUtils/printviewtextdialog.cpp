#include "printviewtextdialog.h"
#include <QtGui>

PrintViewTextDialog::PrintViewTextDialog(QWidget *parent) :
    QDialog(parent)
{
    QHBoxLayout *hlay1 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    content = new QTextEdit;

    QPushButton *ok= new QPushButton("Print");
    ok->setDefault(true);
    QPushButton *cancel= new QPushButton("Cancel Printing");

    hlay1->addStretch();
    hlay1->addWidget(cancel);
    hlay1->addWidget(ok);


    mainLayout->addWidget(content);
    mainLayout->addLayout(hlay1);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(reject()));
}

bool PrintViewTextDialog::setView(QString contnt)
{
    QFont font;
    font.setFixedPitch(true);
    font.setStyleHint(QFont::Monospace);
    content->setFont(font);
    content->setPlainText(contnt);
    showMaximized();
    if(exec())
        return true;
    return false;
}
