#ifndef PRINTMODULE_H
#define PRINTMODULE_H

#include <QtCore>
#include <QObject>

class QWebView;

class PrintModule: public QObject
{
    Q_OBJECT
public:
    PrintModule();
    void setPreviewMode(bool mode);
    void setNoOfCopies(int copies);
    void printBillHtml(QStringList invoiceData, QStringList customerDetails, QStringList table, QStringList summary);
    void printReportHtml(QStringList reportData, QStringList table);
    void printChellanHtml(QStringList invoiceData, QStringList customerDetails, QStringList table, QStringList summary, QStringList chellanDetails);
    void printHTML(QString htmlContent);
    void setFilename(QString filname);
    void setDirecory(QString directory);

private:
    bool previewMode; // true - Need Preview, false- Not Need Preview
    int noCopies; // No of copies required
    QWebView *webView;

    QString directory;
    QString filename;
    QString getHtmlBillFormat();
    QString getHtmlTable(QStringList table);

protected slots:
    void printFile();
};

#endif // PRINTMODULE_H
