#ifndef STOCKPURCHASEINVOICEWIDGET_H
#define STOCKPURCHASEINVOICEWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QLineEdit;
class QComboBox;
class QSpinBox;

class StockPurchaseInvoiceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StockPurchaseInvoiceWidget(int wid = 500, QWidget *parent = 0);

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

    ListTableWidget *table;

signals:
    void setGrandTotal(QString);
    void setHeader(QString);

public slots:
    void setData();
    void setDate(QDate);
    void checkId(QString);
    void checkCode(QString);
    void clearDealerData();
    void addAnItem();
    void removeItem();
    void returnItem();
    void removeLastItem();
    void clearItems();
    void saveInvoice();
    void printAndSave();
    void saveOnly();
    bool printInvoiceHtml(int from = 0);
    void getChellanInvoiceDialog();
    void totalCorrection(QString total);
};

#endif // STOCKPURCHASEINVOICEWIDGET_H
