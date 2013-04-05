#ifndef SETESTIMATEDIALOG_H
#define SETESTIMATEDIALOG_H

#include <QDialog>

class QLineEdit;

class SetEstimateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetEstimateDialog(QWidget *parent = 0);

private:
    QLineEdit *estimateNo;

signals:

public slots:
    void setEstimateNo();
};

#endif // SETESTIMATEDIALOG_H
