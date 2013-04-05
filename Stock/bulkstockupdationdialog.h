#ifndef BULKSTOCKUPDATIONDIALOG_H
#define BULKSTOCKUPDATIONDIALOG_H

#include <QDialog>
#include "listtablewidget.h"

class BulkStockUpdationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BulkStockUpdationDialog(QWidget *parent = 0);
    void bulkStockUpdation();

private:
    ListTableWidget *updateTable;

signals:
    
public slots:
    void updateAll();
    
};

#endif // BULKSTOCKUPDATIONDIALOG_H
