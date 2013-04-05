#include "changepassworddialog.h"
#include <QtGui>
#include "commons.h"

#define LABEL_WIDTH 150
#define INPUT_WIDTH 150

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Change Password - Dialog");

    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;
    hlay3 = new QHBoxLayout;
    hlay4 = new QHBoxLayout;

    QLabel *label1 = new QLabel("Current Password: ");
    label1->setMinimumWidth(LABEL_WIDTH);
    QLabel *label2 = new QLabel("New Password: ");
    label2->setMinimumWidth(LABEL_WIDTH);
    QLabel *label3 = new QLabel("Confirm Password: ");
    label3->setMinimumWidth(LABEL_WIDTH);

    currentPassword = new QLineEdit;
    currentPassword->setEchoMode(QLineEdit::Password);
    currentPassword->setMinimumWidth(INPUT_WIDTH);
    newPassword = new QLineEdit;
    newPassword->setEchoMode(QLineEdit::Password);
    newPassword->setMinimumWidth(INPUT_WIDTH);
    confirmPassword = new QLineEdit;
    confirmPassword->setEchoMode(QLineEdit::Password);
    confirmPassword->setMinimumWidth(INPUT_WIDTH);
    QLabel *message = new QLabel;
    QPushButton *cancelButton = new QPushButton("Cancel");
    QPushButton *changePasswordButton = new QPushButton("Change Password");
    changePasswordButton->setDefault(true);

    hlay1->addWidget(label1);
    hlay1->addWidget(currentPassword);
    hlay2->addWidget(label2);
    hlay2->addWidget(newPassword);
    hlay3->addWidget(label3);
    hlay3->addWidget(confirmPassword);
    hlay4->addStretch();
    hlay4->addWidget(cancelButton);
    hlay4->addWidget(changePasswordButton);

    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);
    mainLayout->addLayout(hlay3);
    mainLayout->addWidget(message);
    mainLayout->addLayout(hlay4);

    connect(this, SIGNAL(setMessage(QString)), message, SLOT(setText(QString)));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(changePasswordButton, SIGNAL(clicked()), this, SLOT(accept()));
}

void ChangePasswordDialog::getPasswordDialog(QString message)
{
    setMessage(message);
    if(exec())
    {
        QString current = currentPassword->text();
        QString adminPassword = Commons::getAdminPassword();
        if(current != adminPassword)
        {        qDebug()<<"Debug";

            getPasswordDialog("<font color=red><b>Current Password doesn't match!");
            return;
        }
        if(newPassword->text() != confirmPassword->text())
        {
            getPasswordDialog("<font color=red><b>Password confimatiion failed!!");
            return;
        }
        Commons::setAdminPassword(newPassword->text());
    }
}

