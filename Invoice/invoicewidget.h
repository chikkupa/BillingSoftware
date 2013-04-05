#ifndef INVOICEWIDGET_H
#define INVOICEWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QLineEdit;
class QComboBox;
class QSpinBox;

class InvoiceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InvoiceWidget(int wid=0, QWidget *parent = 0);

private:
    int width;
    QDate invoiceDate;
    QStringList ids;
    QStringList names;
    QStringList values;
    QStringList comIds;
    QStringList commodities;
    QStringList comValues;
    QStringList tableValues;

    QSpinBox *noPrints;
    QComboBox *id;
    QLineEdit *name;
    QLineEdit *address;
    QLineEdit *phoneNo;
    QLineEdit *mobile;
    QLineEdit *email;

    QComboBox *comId;
    QComboBox *commodity;
    QLineEdit *quantity;
    QLineEdit *tax;
    QLineEdit *price;
    QLineEdit *discount;
    QLineEdit *payment;

    ListTableWidget *table;

signals:
    void setGrandTotal(QString);
    void setHeader(QString);
    void setBalance(QString);

public slots:
    void setData();
    void setDate(QDate);
    void checkId(QString);
    void checkCode(QString);
    void clearDealerData();
    void addAnItem();
    float getPrevouslyAddedQty(QString commodityId);
    void returnItem();
    void removeItem();
    void removeLastItem();
    void clearItems();
    void saveInvoice();
    void printAndSave();
    void saveOnly();
    bool printInvoiceHtml(int from = 0);
    void getChellanInvoiceDialog();
    void getBalance();
    void totalCorrection(QString total);
};

#endif // INVOICEWIDGET_H
