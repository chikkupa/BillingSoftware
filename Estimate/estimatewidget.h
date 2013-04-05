#ifndef ESTIMATEWIDGET_H
#define ESTIMATEWIDGET_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QLineEdit;
class QComboBox;
class QSpinBox;

class EstimateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EstimateWidget(int wid = 500, QWidget *parent = 0);

private:
    int width;
    QDate estimateDate;
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
    void removeLastItem();
    void clearItems();
    void saveEstimate();
    void printAndSave();
    void saveOnly();
    bool printEstimateHtml(int from = 0);
    void totalCorrection(QString total);
};

#endif // ESTIMATEWIDGET_H
