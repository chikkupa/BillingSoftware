#ifndef OLDESTIMATES_H
#define OLDESTIMATES_H

#include <QWidget>
#include "listtablewidget.h"
#include <QDate>

class QLineEdit;
class QComboBox;
class QSpinBox;

class OldEstimates : public QWidget
{
    Q_OBJECT
public:
    explicit OldEstimates(int wid = 500, QWidget *parent = 0);

private:
    int width;
    QDate estimateDate;
    QString currentEstimateNo;
    QStringList ids;
    QStringList names;
    QStringList values;
    QStringList comIds;
    QStringList commodities;
    QStringList comValues;
    QStringList tableValues;

    QSpinBox *estimateNo;
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
    void setDateEdit(QDate);

public slots:
    void setData();
    void setDate(QDate);
    void setEstimateNo(int);
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


#endif // OLDESTIMATES_H
