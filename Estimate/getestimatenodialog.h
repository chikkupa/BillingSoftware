#ifndef GETESTIMATENODIALOG_H
#define GETESTIMATENODIALOG_H

#include <QDialog>

class QLineEdit;

class GetEstimateNoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GetEstimateNoDialog(QWidget *parent = 0);

    QLineEdit *estimateNo;

signals:

public slots:
    QString getEstimateNo();
};

#endif // GETESTIMATENODIALOG_H
