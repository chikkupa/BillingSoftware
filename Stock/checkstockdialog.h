#ifndef CHECKSTOCKDIALOG_H
#define CHECKSTOCKDIALOG_H

#include <QDialog>

class QComboBox;
class QLineEdit;

class CheckStockDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckStockDialog(QWidget *parent = 0);
    bool checkStock();

private:
    bool status;
    QStringList ids;
    QStringList values;

    QComboBox *code;
    QPushButton *closeButton;

signals:
    void setDescription(QString);

public slots:
    void checkId(QString);

};

#endif // CHECKSTOCKDIALOG_H
