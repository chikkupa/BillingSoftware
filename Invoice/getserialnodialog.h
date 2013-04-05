#ifndef GETSERIALNODIALOG_H
#define GETSERIALNODIALOG_H

#include <QDialog>

class QLineEdit;

class GetSerialNoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GetSerialNoDialog(QWidget *parent = 0);

    QLineEdit *serialNo;

signals:

public slots:
    QString getSerialNo();
};


#endif // GETSERIALNODIALOG_H
