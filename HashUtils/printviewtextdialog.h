#ifndef PRINTVIEWTEXTDIALOG_H
#define PRINTVIEWTEXTDIALOG_H

#include <QDialog>

class QTextEdit;

class PrintViewTextDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PrintViewTextDialog(QWidget *parent = 0);

private:
    QTextEdit *content;

signals:

public slots:
    bool setView(QString);

};

#endif // PRINTVIEWTEXTDIALOG_H
