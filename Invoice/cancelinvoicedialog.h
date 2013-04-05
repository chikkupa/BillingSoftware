#ifndef CANCELINVOICEDIALOG_H
#define CANCELINVOICEDIALOG_H

#include <QDialog>

class QRadioButton;
class QLineEdit;

class CancelInvoiceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CancelInvoiceDialog(QWidget *parent = 0);
    QRadioButton *typeSingle;
    QRadioButton *typeMultiple;
    QLineEdit *invoiceNo;
    QLineEdit *invoiceNo1;
    QLineEdit *invoiceNo2;

signals:

public slots:
    void cancelInvoice();
    void setSingleType(bool);
    void setMultiType(bool);

};

#endif // CANCELINVOICEDIALOG_H
