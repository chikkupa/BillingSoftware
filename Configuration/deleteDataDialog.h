#ifndef EXPORTPDFDIALOG_H
#define EXPORTPDFDIALOG_H

#include <QDialog>

class QCheckBox;
class QDateEdit;

class DeleteDataDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeleteDataDialog(QWidget *parent = 0);

private:
    QCheckBox *accounts;
    QCheckBox *estimate;
    QCheckBox *invoice;
    QCheckBox *stock;
    
signals:
    
public slots:
    void getDeleteDataDialog();
    
};

#endif // EXPORTPDFDIALOG_H
