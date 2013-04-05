#ifndef STOCKUPDATIONDIALOG_H
#define STOCKUPDATIONDIALOG_H

#include <QDialog>

class QComboBox;
class QLineEdit;

class StockUpdationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StockUpdationDialog(QWidget *parent = 0);
    bool stockAddition();

private:
    bool status;
    QStringList ids;
    QStringList values;

    QComboBox *code;
    QLineEdit *stock;
    QPushButton *ok;

signals:
    void setDescription(QString);

public slots:
    void checkId(QString);

};

#endif // STOCKUPDATIONDIALOG_H
