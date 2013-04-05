#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include <QDialog>

class QLineEdit;
class QTextEdit;
class QCheckBox;

class ConfigurationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigurationDialog(int wid = 500, QWidget *parent = 0);

    int width;
    QLineEdit *shopName;
    QTextEdit *address;
    QLineEdit *phoneNo;
    QLineEdit *tinNo;
    QLineEdit *cstReg;
    QLineEdit *invoiceNo;
    QLineEdit *estimateNo;
    QLineEdit *purchaseNo;
    QCheckBox *stockCheck;
    QCheckBox *returnItem;

signals:

public slots:
    void getConfiguration();
    void saveData();
};

#endif // CONFIGURATIONWIDGET_H
