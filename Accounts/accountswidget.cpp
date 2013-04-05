#include "accountswidget.h"
#include <QtGui>
#include "databaseserver.h"
#include "commons.h"

AccountsWidget::AccountsWidget(int wid, QWidget *parent) :
    QWidget(parent)
{
    width = wid;
    QHBoxLayout *hlayout1= new QHBoxLayout;
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    QHBoxLayout *hlayout3 = new QHBoxLayout;
    QHBoxLayout *hlayout5 = new QHBoxLayout;
    QHBoxLayout *hlayout6 = new QHBoxLayout;

    QVBoxLayout *vlay1 = new QVBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout(this);

    QLabel *head = new QLabel;
    QLabel *header = new QLabel("<font size=4><center><b><br>Company Accounts Management<br><b></center></font");
    QLabel *label1 = new QLabel("<b>Type</b>:  ");
    QLabel *label2 = new QLabel("<b><center>Amount:  </center></b>");
    QLabel *label3 = new QLabel("<b><center>Description:  </center></b>");
    QLabel *label7 = new QLabel("<center><b>Date</b></center>");

    QLabel *label4 = new QLabel("<center>Account details between date </center>");
    QLabel *label5 = new QLabel("<center> and </center>");

    QLabel *label6 = new QLabel("<center><b><br>Account Details</b></center>");

    label4->setMinimumWidth(150);
    label5->setMinimumWidth(150);

    label2->setMinimumWidth(150);

    radio1 = new QRadioButton("Credit", this);
    radio2 = new QRadioButton("Debit", this);
    radio1->setChecked(true);
    amount= new QLineEdit;
    QRegExp regExp("[0-9]*");
    amount->setValidator(new QRegExpValidator(regExp, this));
    description = new QLineEdit;
    date = new QDateEdit;
    proceed= new QPushButton("To Account");
    proceed->setDefault(true);
    date1 = new QDateEdit;
    date2 = new QDateEdit;
    table = new ListTableWidget;
    QLabel *summary = new QLabel;
    QPushButton *deleteItem = new QPushButton("Delete Item");
    deleteItem->setToolTip("Click on the SlNo of the row to be deleted and click the button");
    deleteItem->setShortcut(QKeySequence(tr("Shift+Ctrl+D")));

    hlayout1->addWidget(head);

    hlayout5->addWidget(header);

    hlayout2->addWidget(label1);
    hlayout2->addWidget(radio1);
    hlayout2->addWidget(radio2);
    hlayout2->addWidget(label2);
    hlayout2->addWidget(amount);
    hlayout2->addWidget(label3);
    hlayout2->addWidget(description);
    hlayout2->addWidget(label7);
    hlayout2->addWidget(date);
    hlayout2->addWidget(proceed);
    hlayout2->addWidget(deleteItem);

    hlayout3->addStretch();
    hlayout3->addWidget(label4);
    hlayout3->addWidget(date1);
    hlayout3->addWidget(label5);
    hlayout3->addWidget(date2);
    hlayout3->addStretch();

    hlayout6->addStretch();
    hlayout6->addLayout(vlay1);
    hlayout6->addStretch();

    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout5);
    vlayout->addLayout(hlayout2);
    vlayout->addWidget(label6);
    vlayout->addLayout(hlayout3);
    vlayout->addWidget(table);
    vlayout->addWidget(summary);

    connect(proceed, SIGNAL(clicked()), this, SLOT(toDatabase()));
    connect( this, SIGNAL(setHead(QString)), head, SLOT(setText(QString)));
    connect(date1, SIGNAL(dateChanged(QDate)), this, SLOT(clearFields()));
    connect(date2, SIGNAL(dateChanged(QDate)), this, SLOT(clearFields()));
    connect( this, SIGNAL(setSummery(QString)), summary, SLOT(setText(QString)));
    connect( deleteItem, SIGNAL(clicked()), this, SLOT(deleteItem()));
 }

void AccountsWidget::setDetails()
{
    setHead(Commons::getHeaderWithAddress());
    date->setDate(QDate::currentDate());
    date1->setDate(QDate::currentDate());
    date2->setDate(QDate::currentDate());
    clearFields();
}

 void AccountsWidget::toDatabase()
 {
    if(!validateFields())
    {
        //showResult("Cannot add transaction<br>Error: Some fields are empty", 1);
        return;
    }
    QString type = radio1->isChecked()? "Credit" : "Debit";
    QString amt = amount->text();
    QString descr = description->text();
    QString dte =  date->date().toString("yyyy-MM-dd");

    DatabaseServer *server = new DatabaseServer;
    server->executeQuery("insert into Accounts (Type,Amount,FormOf,Date) values ('" + type + "'," + amt + ",'" + descr + "','" + dte + "')");
    delete server;
    clearFields();
}

bool AccountsWidget::validateFields()
{
    if( amount->text() == "")
        return false;
    return true;
}

void AccountsWidget::clearFields()
{
    radio1->setChecked(true);
    amount->setText("");
    description->setText("");
    date->setDate(QDate::currentDate());
    QString start = date1->date().toString("yyyy-MM-dd");
    QString end = date2->date().toString("yyyy-MM-dd");
    DatabaseServer server;
    QString query = "select SlNo,Type,Amount,FormOf as Description,Date from Accounts where Date>='" + start + "' and Date<='" + end + "'";
    QStringList list = server.getListTableResult(query);
    qDebug()<<list;
    table->setList(list);
    for(int i=0; i<table->columnCount(); i++)
    {
        table->setColumnWidth(i,(width-50)/table->columnCount());
    }

    QString debit = server.getSingleResult("select sum(Amount) from Accounts where Type='Debit' and Date>='" + start + "' and Date<='" + end + "'");
    QString credit = server.getSingleResult("select sum(Amount) from Accounts where Type='Credit' and Date>='" + start + "' and Date<='" + end + "'");

    setSummery("<b><center><font size=4>Total Credits: " + credit + "<br>Total Debits: " + debit + "<br><font size=5>Summery: " + QString::number(credit.toFloat() - debit.toFloat()));
}

void AccountsWidget::deleteItem()
{
    QModelIndex index = table->currentIndex();
    QVariant row = index.data();
    QString value = row.toString();
    if(index.column() == 0)
    {
        DatabaseServer server;
        server.executeQuery("delete from Accounts where SlNo=" + value);
    }
    clearFields();
}

void AccountsWidget::clearAll()
{
    QString start = date1->date().toString("yyyy-MM-dd");
    QString end = date2->date().toString("yyyy-MM-dd");
    DatabaseServer server;
    server.executeQuery("delete from Accounts where Date>='" + start + "' and Date<='" + end + "'");
}
