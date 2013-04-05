#ifndef CHELLANINVOICEDIALOG_H
#define CHELLANINVOICEDIALOG_H

#include <QDialog>

class QLineEdit;
class QTextEdit;

class ChellanInvoiceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChellanInvoiceDialog(QWidget *parent = 0);

private:
    QLineEdit *deliveryNote;
    QLineEdit *modeOfPayement;
    QLineEdit *suppliersRef;
    QLineEdit *otherRef;
    QLineEdit *orderNo;
    QLineEdit *orderDate;
    QLineEdit *despatchNo;
    QLineEdit *despatchDate;
    QLineEdit *despatchThrough;
    QLineEdit *destination;
    QTextEdit *consignee;
    QTextEdit *buyer;
    QTextEdit *termsOfDelivery;

signals:

public slots:
    QStringList getChellanInvoiceDetails(QStringList address, QString invoiceNo);

};

#endif // CHELLANINVOICEDIALOG_H
