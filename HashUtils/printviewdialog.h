#ifndef PRINTVIEWDIALOG_H
#define PRINTVIEWDIALOG_H

#include <QDialog>
#include <QtWebKit>

class PrintViewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PrintViewDialog(QWidget *parent = 0);

    QWebView *webView;

signals:

public slots:
    bool setwebView(QString htmlContent, QString directory = "");
};

#endif // PRINTVIEWDIALOG_H
