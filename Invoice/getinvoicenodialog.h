#ifndef GETINVOICENODIALOG_H
#define GETINVOICENODIALOG_H

#include <QDialog>

class QLineEdit;

class GetInvoiceNoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GetInvoiceNoDialog(QWidget *parent = 0);

    QLineEdit *invoiceNo;

signals:

public slots:
    QString getInvoiceNo();
};

#endif // GETINVOICENODIALOG_H
