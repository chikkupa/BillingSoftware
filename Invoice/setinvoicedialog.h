#ifndef SETINVOICEDIALOG_H
#define SETINVOICEDIALOG_H

#include <QDialog>

class QLineEdit;

class setInvoiceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit setInvoiceDialog(QWidget *parent = 0);

private:
    QLineEdit *invoiceNo;

signals:

public slots:
    void setInvoiceNo();
};

#endif // SETINVOICEDIALOG_H
