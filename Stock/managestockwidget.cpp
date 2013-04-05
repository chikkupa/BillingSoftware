#include "managestockwidget.h"
#include <QtGui>
#include "tablecommodity.h"
#include "messages.h"
#include "commons.h"
#include "printmodule.h"

#define LABELWIDTH 120
#define BUTTONWIDTH 100

ManageStockWidget::ManageStockWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    int inputWidth = (width - 3 * LABELWIDTH - 50) / 3;

    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4, *hlay5;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;
    hlay3 = new QHBoxLayout;
    hlay4 = new QHBoxLayout;
    hlay5 = new QHBoxLayout;

    QLabel *header = new QLabel(Commons::getHeaderWithAddress());

    QLabel *stockHead = new QLabel("<b><center>Stock Details</center></b>");
    QLabel *label1 = new QLabel("Commodity Id: ");
    QLabel *label2 = new QLabel("Commodity Name: ");
    QLabel *label3 = new QLabel("Tax: ");
    QLabel *label7 = new QLabel("Purchsase Price: ");
    QLabel *label4 = new QLabel("Sales Price: ");
    QLabel *label5 = new QLabel("Cess: ");
    QLabel *label6 = new QLabel("Stock: ");
    QLabel *label8 = new QLabel("Total(For Price Adj:)");
    QLabel *label9 = new QLabel("Search By ");
    QLabel *label10 = new QLabel("Search Key ");
    QLabel *message = new QLabel;

    label1->setMinimumWidth(LABELWIDTH);
    label2->setMinimumWidth(LABELWIDTH);
    label3->setMinimumWidth(LABELWIDTH);
    label4->setMinimumWidth(LABELWIDTH);
    label5->setMinimumWidth(LABELWIDTH);
    label6->setMinimumWidth(LABELWIDTH);
    label7->setMinimumWidth(LABELWIDTH);
    label8->setMinimumWidth(LABELWIDTH);

    QRegExp regExp("[0-9]*([.][0-9]*)?");
    oldId = new QLineEdit;
    commodityId = new QLineEdit;
    commodityName = new QLineEdit;
    tax = new QLineEdit;
    tax->setValidator(new QRegExpValidator(regExp, this));
    purchasePrice = new QLineEdit;
    purchasePrice->setValidator(new QRegExpValidator(regExp, this));
    price = new QLineEdit;
    price->setValidator(new QRegExpValidator(regExp, this));
    cess = new QLineEdit;
    cess->setValidator(new QRegExpValidator(regExp, this));
    stock = new QLineEdit;
    stock->setValidator(new QRegExpValidator(regExp, this));
    totalAdj = new QLineEdit;
    totalAdj->setValidator(new QRegExpValidator(regExp, this));
    searchBy = new QComboBox;
    QStringList list;
    list<<"Id"<<"Name";
    searchBy->addItems(list);
    searchType = new QComboBox;
    list.clear();
    list<<"Starting With"<<"Ending With"<<"Equals"<<"Contains";
    searchType->addItems(list);
    searchKey = new QLineEdit;
    productTable = new ListTableWidget;
    QPushButton *addButton = new QPushButton("Add");
    addButton->setMinimumWidth(BUTTONWIDTH);
    QPushButton *deleteButton = new QPushButton("Delete");
    deleteButton->setMinimumWidth(BUTTONWIDTH);
    QPushButton *updateButton = new QPushButton("Update");
    updateButton->setMinimumWidth(BUTTONWIDTH);
    QPushButton *printButton = new QPushButton("Print");
    printButton->setMinimumWidth(BUTTONWIDTH);

    hlay1->addWidget(label1);
    hlay1->addWidget(commodityId);
    hlay1->addWidget(label2);
    hlay1->addWidget(commodityName);
    hlay1->addWidget(label3);
    hlay1->addWidget(tax);
    hlay1->addWidget(label7);
    hlay1->addWidget(purchasePrice);
    hlay2->addWidget(label4);
    hlay2->addWidget(price);
    hlay2->addWidget(label5);
    hlay2->addWidget(cess);
    hlay2->addWidget(label6);
    hlay2->addWidget(stock);
    hlay2->addWidget(label8);
    hlay2->addWidget(totalAdj);
    hlay3->addWidget(message);
    hlay3->addStretch();
    hlay3->addWidget(addButton);
    hlay3->addWidget(deleteButton);
    hlay3->addWidget(updateButton);
    hlay4->addStretch();
    hlay4->addWidget(label9);
    hlay4->addWidget(searchBy);
    hlay4->addWidget(searchType);
    hlay4->addWidget(label10);
    hlay4->addWidget(searchKey);
    hlay4->addStretch();
    hlay5->addWidget(printButton);
    hlay5->addStretch();

    mainLayout->addWidget(header);
    mainLayout->addWidget(stockHead);
    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);
    mainLayout->addLayout(hlay3);
    mainLayout->addLayout(hlay4);
    mainLayout->addWidget(productTable);
    mainLayout->addLayout(hlay5);

    connect( this, SIGNAL(setMessage(QString)), message, SLOT(setText(QString)));
    connect( productTable, SIGNAL(clicked(QModelIndex)), this, SLOT(populateDetails(QModelIndex)));
    connect( totalAdj, SIGNAL(textChanged(QString)), this, SLOT(totalCorrection(QString)));
    connect( addButton, SIGNAL(clicked()), this, SLOT(addProduct()));
    connect( deleteButton, SIGNAL(clicked()), this, SLOT(deleteProduct()));
    connect( updateButton, SIGNAL(clicked()), this, SLOT(updateProduct()));
    connect( searchKey, SIGNAL(textChanged(QString)), this, SLOT(setData()));
    connect( printButton, SIGNAL(clicked()), this, SLOT(printReport()));
}

void ManageStockWidget::setData()
{
    prodIds.clear();
    products.clear();
    prodIds = TableCommodity::getCommodityIds();
    products = TableCommodity::getAllCommodities();
    clearFields();
    productTable->setList(TableCommodity::getCommodityTable(searchBy->currentText(), searchType->currentIndex() + 1, searchKey->text()));
    for(int i = 0; i < productTable->columnCount(); i++)
    {
        productTable->setColumnWidth(i, (width-50) / productTable->columnCount());
    }
}

void ManageStockWidget::addProduct()
{
    if(!idAvailable(this->commodityId->text()))
    {
        emit setMessage("<center><font color=red><b>Id not available<b></font></center>");
        return;
    }
    if(!validateFields())
    {
        emit setMessage("<center><font color=red><b>Id or/or Name Field Empty<b></font></center>");
        return;
    }
    QString id = this->commodityId->text();
    QString name = this->commodityName->text();
    QString tax = QString::number(this->tax->text().toFloat(), 'f', 2);
    QString purchasePrice = QString::number(this->purchasePrice->text().toFloat(), 'f', 2);
    QString price = QString::number(this->price->text().toFloat(), 'f', 2);
    QString cess = QString::number(this->cess->text().toFloat(), 'f', 2);
    QString stock = QString::number(this->stock->text().toFloat(), 'f', 2);

    TableCommodity::addNewItem(id, name, tax, purchasePrice, price, cess, stock);
    setData();
}

void ManageStockWidget::deleteProduct()
{
    if(idAvailable(this->oldId->text()))
    {
        emit setMessage("<center><font color=red><b>Invalid Id<b></font></center>");
        return;
    }

    QString message = "Are you sure want to remove the product?";
    QString title = "Confirm Delete";

    if(Messages::confirmMessage(message, title))
    {
        TableCommodity::removeItem(this->oldId->text());
    }
    setData();
}

void ManageStockWidget::updateProduct()
{
    if(idAvailable(this->oldId->text()))
    {
        emit setMessage("<center><font color=red><b>Invalid Id<b></font></center>");
        return;
    }

    if(!validateFields())
    {
        emit setMessage("<center><font color=red><b>Id and/or Name Field Empty<b></font></center>");
        return;
    }
    QString oldId = this->oldId->text();
    QString id = this->commodityId->text();
    QString name = this->commodityName->text();
    QString tax = this->tax->text();
    QString purchasePrice = this->purchasePrice->text();
    QString price = this->price->text();
    QString cess = this->cess->text();
    QString stock = this->stock->text();

    TableCommodity::editItem(id, name, tax, purchasePrice, price, cess, stock, oldId);
    setData();
}

QStringList ManageStockWidget::getDetails(QString id)
{
    QStringList details;
    for(int i = 0; i < products.size(); i++)
    {
        QStringList temp = products.at(i).split("\n");
        if(temp.at(0) == id)
        {
            details = temp;
        }
    }
    return details;
}

void ManageStockWidget::populateDetails(QModelIndex index)
{
    QVariant row = index.data();
    if(index.column() == 0)
    {
        QString value = row.toString();
        commodityId->setText(value);
        oldId->setText(value);
        QStringList details = getDetails(value);
        if(details.size() > 0)
        {
            commodityName->setText(details.at(1));
            tax->setText(details.at(2));
            purchasePrice->setText(details.at(3));
            price->setText(details.at(4));
            cess->setText(details.at(5));
            stock->setText(details.at(6));
        }
    }
}

bool ManageStockWidget::idAvailable(QString id)
{
    for(int i = 0; i < prodIds.size(); i++)
    {
        if(prodIds.at(i) == id)
            return false;
    }
    return true;
}

bool ManageStockWidget::validateFields()
{
    QString id = this->commodityId->text();
    QString name = this->commodityName->text();

    if(id.trimmed() != "" && name.trimmed() != "")
        return true;
    return false;
}

void ManageStockWidget::totalCorrection(QString total)
{
    float nTotal = total.toFloat();
    float nTax = tax->text().toFloat();
    float nGross = (100 * nTotal) / (100 + nTax);

    price->setText(QString::number(nGross, 'f', 6));
}


void ManageStockWidget::clearFields()
{
    oldId->setText("");
    commodityId->setText("");
    commodityName->setText("");
    tax->setText("");
    purchasePrice->setText("");
    price->setText("");
    cess->setText("");
    stock->setText("");
    totalAdj->setText("");
    emit setMessage("");
}

void ManageStockWidget::printReport()
{
    QStringList reportData;
    reportData.append(QDate::currentDate().toString("dd/MM/yyyy"));
    QStringList tableData;
    for(int i =0; i < productTable->rowCount(); i++)
    {
        QString column;
        for(int j = 0; j < productTable->columnCount(); j++)
        {
            column += productTable->getItem(i, j);
            if(j != productTable->columnCount()-1)
                column += "\n";
        }
        tableData.append(column);
    }

    PrintModule *pm = new PrintModule;
    pm->setPreviewMode(true);
    pm->setNoOfCopies(1);
    pm->setDirecory("Prints");
    pm->setFilename("stock.html");
    pm->printReportHtml(reportData, tableData);
}
