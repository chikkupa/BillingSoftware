#ifndef ADDNEWSTOCKDIALOG_H
#define ADDNEWSTOCKDIALOG_H

#include <QDialog>

class QLineEdit;
class QLabel;
class QPushButton;

class AddNewStockDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddNewStockDialog(QWidget *parent = 0);
    void addNewStock();

private:
    QStringList record;
    bool status;

    QLineEdit *code;
    QLineEdit *name;
    QLineEdit *tax;
    QLineEdit *purchasePrice;
    QLineEdit *value;
    QLineEdit *cess;
    QLineEdit *stock;
    QLabel *message;
    QPushButton *ok;
signals:

public slots:
    void checkFilled(QString);
    void checkCode(QString);
};

#endif // ADDNEWSTOCKDIALOG_H
