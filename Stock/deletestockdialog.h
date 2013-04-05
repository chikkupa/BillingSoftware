#ifndef DELETESTOCKDIALOG_H
#define DELETESTOCKDIALOG_H

#include <QDialog>

class QComboBox;
class QLabel;

class deleteStockDialog : public QDialog
{
    Q_OBJECT
public:
    explicit deleteStockDialog(QWidget *parent = 0);
    void deleteStock();

private:
    bool status;
    QStringList ids;
    QStringList values;

    QComboBox *code;
    QLabel *description;
    QPushButton *ok;

signals:

public slots:
    void checkId(QString);

};

#endif // DELETESTOCKDIALOG_H
