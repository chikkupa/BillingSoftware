#ifndef UPDATESTOCKDETAILSDIALOG_H
#define UPDATESTOCKDETAILSDIALOG_H

#include <QDialog>

class QComboBox;
class QLineEdit;
class QPushButton;

class UpdateStockDetailsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UpdateStockDetailsDialog(QWidget *parent = 0);
    void updateStockDetails();

private:
    QStringList ids;
    QStringList values;
    bool status;

    QComboBox *codeCombo;
    QLineEdit *code;
    QLineEdit *name;
    QLineEdit *tax;
    QLineEdit *purchasePrice;
    QLineEdit *value;
    QLineEdit *cess;
    QLineEdit *stock;
    QPushButton *ok;
signals:

public slots:
    void checkFilled(QString);
    void checkId(QString);
};

#endif // UPDATESTOCKDETAILSDIALOG_H
