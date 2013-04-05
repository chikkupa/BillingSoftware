#include "messages.h"
#include <QMessageBox>

Messages::Messages()
{
}

void Messages::showMessage(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

void Messages::showCriticalMessage(QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(message);
    msgBox.exec();
}

bool Messages::confirmMessage(QString message, QString title)
{
    QString text = message;

    QMessageBox msg(title, text, QMessageBox::
    Critical, QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape, QMessageBox::NoButton);

    if(msg.exec()== QMessageBox::Yes)
        return true;
    return false;
}
