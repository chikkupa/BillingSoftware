#include "checkstockdialog.h"
#include <QtGui>
#include "databaseserver.h"

CheckStockDialog::CheckStockDialog(QWidget *parent) :
    QDialog(parent)
{
    status = true;
    setWindowTitle("Stock Check- Dialog");
    resize(600,300);
    QHBoxLayout *hlay1, *hlay2, *hlay3;
    QVBoxLayout *mainLayout;

    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;
    hlay3 = new QHBoxLayout;

    mainLayout = new QVBoxLayout(this);

    QLabel *label1 = new QLabel("Item Code: ");
    code = new QComboBox;
    code->setEditable(true);
    QLabel *description = new QLabel;

    closeButton = new QPushButton("Close");

    hlay1->addWidget(label1);
    hlay1->addWidget(code);
    hlay2->addWidget(description);
    hlay3->addStretch();
    hlay3->addWidget(closeButton);
    mainLayout->addLayout(hlay1);
    mainLayout->addStretch();
    mainLayout->addLayout(hlay2);
    mainLayout->addStretch();
    mainLayout->addStretch();
    mainLayout->addLayout(hlay3);

    setAttribute(Qt::WA_QuitOnClose);

    connect(code, SIGNAL(currentIndexChanged(QString)), this, SLOT(checkId(QString)));
    connect(this, SIGNAL(setDescription(QString)), description, SLOT(setText(QString)));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(accept()));
}

bool CheckStockDialog::checkStock()
{
    DatabaseServer server;
    ids.clear();
    ids.append("");
    ids.append(server.getListResult("select Id from Commodity;"));
    code->clear();
    values.clear();
    values = server.getMultiListResult("select Name, PurchasePrice, Price, Quantity from Commodity;");
    if(values.size() > 0)
    {
        code->addItems(ids);
        QCompleter *completer1 = new QCompleter(code);
        completer1->setCaseSensitivity(Qt::CaseInsensitive);
        QStringListModel *listModel1 = new QStringListModel(completer1);
        listModel1->setStringList(ids);
        completer1->setModel(listModel1);
        completer1->setCompletionMode(QCompleter::PopupCompletion);
        code->setCompleter(completer1);
    }
    if(exec())
    {
        return true;
    }
    return false;
}

void CheckStockDialog::checkId(QString text)
{
    int ind = -1;
    for(int i=0; i< ids.size(); i++)
    {
        if(ids.at(i) == text)
            ind = i;
    }
    if( ind <= 0)
    {
        status = false;
        setDescription("<center><b><font color=red>Item not found!!</font></b></center>");
        return;
    }
    status =true;
    QStringList data = values.at(ind - 1).split("\n");
    QString displayString = "<center><b><table width='80%'><tr><td>Item Name: </td><td>"+ data.at(0) + "</td></tr>";
    displayString += "<tr><td>Purchase Price: </td><td>" + data.at(1) + "</td></tr>";
    displayString += "<tr><td>Value: </td><td>" + data.at(2) + "</td></tr>";
    displayString += "<tr><td>Stock Remaining: </td><td>" + data.at(3) + "</td></tr></table></center>";
    setDescription(displayString);
}

