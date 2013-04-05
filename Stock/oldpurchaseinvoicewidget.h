#ifndef OLDPURCHASEINVOICEWIDGET_H
#define OLDPURCHASEINVOICEWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QLineEdit;
class QComboBox;
class QSpinBox;

class OldPurchaseInvoiceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OldPurchaseInvoiceWidget(int wid = 500, QWidget *parent = 0);
private:
    int width;
    QDate invoiceDate;
    QString currentInvoiceNo;
    QStringList ids;
    QStringList names;
    QStringList values;
    QStringList comIds;
    QStringList commodities;
    QStringList comValues;
    QStringList tableValues;

    QSpinBox *invoiceNo;
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

    ListTableWidget *table;

signals:
    void setGrandTotal(QString);
    void setHeader(QString);
    void setDateEdit(QDate);

public slots:
    void setData();
    void setDate(QDate);
    void setInvoiceNo(int);
    void checkId(QString);
    void checkCode(QString);
    void clearCustomerData();
    void addAnItem();
    void removeItem();
    void removeLastItem();
    void clearItems();
    void saveInvoice();
    void printAndSave();
    void saveOnly();
    bool printInvoiceHtml(int from = 0);
    void totalCorrection(QString total);
};

#endif // OLDPURCHASEINVOICEWIDGET_H
