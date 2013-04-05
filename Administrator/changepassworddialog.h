#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>

class QLineEdit;

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChangePasswordDialog(QWidget *parent = 0);
    
private:
    QLineEdit *currentPassword;
    QLineEdit *newPassword;
    QLineEdit *confirmPassword;

signals:
    void setMessage(QString);
    
public slots:
    void getPasswordDialog(QString message);

};

#endif // CHANGEPASSWORDDIALOG_H
