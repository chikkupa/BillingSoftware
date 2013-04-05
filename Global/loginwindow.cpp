#include <QtGui>
#include "loginwindow.h"
#include "commons.h"

#define LABEL_WIDTH 150
#define INPUT_WIDTH 150

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("HashInclude IMS - Login");
    setWindowFlags(Qt::CustomizeWindowHint);

    QDesktopWidget *desktop=QApplication::desktop();

    int screenWidth=desktop->width();
    int screenHeight=desktop->height();

    int WIDTH=500;
    int HEIGHT=300;

    int x=(screenWidth-WIDTH)/2;
    int y=(screenHeight-HEIGHT)/2;

    resize(WIDTH, HEIGHT);
    move(x, y);

    QHBoxLayout *hlay1, *hlay2, *hlay3, *hlay4;
    hlay1= new QHBoxLayout;
    hlay2= new QHBoxLayout;
    hlay3= new QHBoxLayout;
    hlay4= new QHBoxLayout;

    QVBoxLayout *mainLayout= new QVBoxLayout(this);

    QLabel *label1= new QLabel("<b>User</b>");
    QLabel *label2= new QLabel("<b>Password<b>");
    QLabel *label3= new QLabel("<center><font size=2><b>Designed and Developed By: HashInclude</b></font></center>");
    QLabel *message = new QLabel;

    label1->setMinimumWidth(LABEL_WIDTH);
    label2->setMinimumWidth(LABEL_WIDTH);

    username= new QComboBox;
    QStringList users;
    users<<"Administrator"<<"Sales";
    username->addItems(users);
    username->setMinimumWidth(INPUT_WIDTH);
    password= new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    password->setMinimumWidth(INPUT_WIDTH);

    QPushButton *cancel= new QPushButton("Cancel");
    QPushButton *login= new QPushButton("Login");
    login->setDefault(true);

    hlay1->addStretch();
    hlay1->addWidget(label1);
    hlay1->addStretch();
    hlay1->addWidget(username);
    hlay1->addStretch();
    hlay2->addStretch();
    hlay2->addWidget(label2);
    hlay2->addStretch();
    hlay2->addWidget(password);
    hlay2->addStretch();
    hlay3->addStretch();
    hlay3->addWidget(cancel);
    hlay3->addWidget(login);
    hlay3->addStretch();
    hlay4->addStretch();
    hlay4->addWidget(message);
    hlay4->addStretch();

    mainLayout->addStretch(3);
    mainLayout->addLayout(hlay1);
    mainLayout->addLayout(hlay2);
    mainLayout->addStretch(1);
    mainLayout->addLayout(hlay4);
    mainLayout->addStretch(1);
    mainLayout->addLayout(hlay3);
    mainLayout->addStretch(1);
    mainLayout->addWidget(label3);

    setAttribute(Qt::WA_QuitOnClose);

    connect(this, SIGNAL(setMessage(QString)), message, SLOT(setText(QString)));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(login, SIGNAL(clicked()), this, SLOT(accept()));
}

QList<int> LoginWindow:: checkLogin(QString message)
{
    QList<int> output;

    setMessage(message);
    QString password;
    this->password->setFocus();

    if(exec())
    {
        if(username->currentIndex() == 0)
            password = Commons::getAdminPassword();
        else if(username->currentIndex() == 1)
            password = Commons::getSalesPassword();

        if(this->password->text() == password)
        {
            output<<1<<username->currentIndex();
            return output;
        }
        else
            return checkLogin("<b><font color=red>Invalid Password</font</b>");
    }
    output<<0<<username->currentIndex();
    return output;
}
