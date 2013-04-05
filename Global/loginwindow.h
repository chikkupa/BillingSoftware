#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QLabel>

class QLineEdit;
class QComboBox;

class LoginWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = 0);

protected:
    QComboBox *username;
    QLineEdit *password;
    QLabel *message;

public slots:
    QList<int> checkLogin(QString message = "");
signals:
    void setMessage(QString);
};

#endif // LOGINWINDOW_H
