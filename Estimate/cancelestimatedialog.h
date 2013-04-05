#ifndef CANCELESTIMATEDIALOG_H
#define CANCELESTIMATEDIALOG_H

#include <QDialog>

class QRadioButton;
class QLineEdit;

class CancelEstimateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CancelEstimateDialog(QWidget *parent = 0);
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
    void clearAll();
    
};

#endif // CANCELESTIMATEDIALOG_H
