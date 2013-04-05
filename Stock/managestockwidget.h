#ifndef MANAGESTOCKWIDGET_H
#define MANAGESTOCKWIDGET_H

#include <QWidget>
#include "listtablewidget.h"

class QLineEdit;
class QComboBox;

class ManageStockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ManageStockWidget(int width = 500, QWidget *parent = 0);

private:
    int width;
    QStringList prodIds;
    QStringList products;

    QLineEdit *oldId;
    QLineEdit *commodityId;
    QLineEdit *commodityName;
    QLineEdit *tax;
    QLineEdit *purchasePrice;
    QLineEdit *price;
    QLineEdit *cess;
    QLineEdit *stock;
    QLineEdit *totalAdj;
    QComboBox *searchBy;
    QComboBox *searchType;
    QLineEdit *searchKey;
    ListTableWidget *productTable;

signals:
    void setMessage(QString);

public slots:
    void setData();

private slots:
    void addProduct();
    void deleteProduct();
    void updateProduct();
    QStringList getDetails(QString id);
    void populateDetails(QModelIndex index);
    bool idAvailable(QString id);
    bool validateFields();
    void totalCorrection(QString total);
    void clearFields();
    void printReport();
};

#endif // MANAGESTOCKWIDGET_H
