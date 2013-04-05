#include "bulkstockupdationdialog.h"
#include <QtGui>
#include "tablecommodity.h"
#include "messages.h"

#define WIDTH 900
#define HEIGHT 540

BulkStockUpdationDialog::BulkStockUpdationDialog(QWidget *parent) :
    QDialog(parent)
{
    resize(WIDTH, HEIGHT);
    setWindowTitle("Bulk Stock Update");

    QHBoxLayout *hlay1;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    hlay1 = new QHBoxLayout;

    updateTable = new ListTableWidget;
    QPushButton *updateButton = new QPushButton("Update");
    updateButton->setDefault(true);
    QPushButton *cancelButton =  new QPushButton("Cancel");

    hlay1->addStretch();
    hlay1->addWidget(cancelButton);
    hlay1->addWidget(updateButton);

    mainLayout->addWidget(updateTable);
    mainLayout->addLayout(hlay1);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(updateButton, SIGNAL(clicked()), this, SLOT(accept()));
}

void BulkStockUpdationDialog::bulkStockUpdation()
{
    updateTable->setList(TableCommodity::getUpdateTable(), true);
    updateTable->setEditableColumn(0, false);
    updateTable->setEditableColumn(1, false);
    updateTable->setEditableColumn(2, false);
    for(int i=0; i<updateTable->columnCount(); i++)
    {
        updateTable->setColumnWidth(i, (WIDTH-50)/updateTable->columnCount());
    }
    updateTable->scrollToTop();
    if(exec())
        updateAll();
}

void BulkStockUpdationDialog::updateAll()
{
    QList<QStringList> tableDetails;

    for(int i = 0; i < updateTable->rowCount(); i++)
    {
        QStringList row;
        for(int j = 0; j < updateTable->columnCount(); j++)
        {
            row.append(updateTable->getItem(i, j));
        }
        tableDetails.append(row);
    }
    TableCommodity::bulkUpdate(tableDetails);
    Messages::showMessage("Items Updated Successfully!!");
}
