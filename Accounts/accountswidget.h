#ifndef ACCOUNTSWIDGET_H
#define ACCOUNTSWIDGET_H

#include <QWidget>
#include "listtablewidget.h"

class QLineEdit;
class QComboBox;
class QPushButton;
class QLabel;
class QRadioButton;
class QDateEdit;

class AccountsWidget : public QWidget
{
    Q_OBJECT
    public:
        explicit AccountsWidget(int wid = 500, QWidget *parent = 0);
        void setDetails();
        bool validateFields();

    private:
        int width;
        QRadioButton *radio1;
        QRadioButton *radio2;
        QLineEdit *amount;
        QLineEdit *description;
        QDateEdit *date;
        QPushButton *proceed;
        QDateEdit *date1;
        QDateEdit *date2;
        ListTableWidget *table;

    protected slots:
        void toDatabase();
        void clearFields();
        void deleteItem();
        void clearAll();

    protected: signals:
        void setHead(QString);
        void setSummery(QString);
    };

#endif // ACCOUNTSWIDGET_H
