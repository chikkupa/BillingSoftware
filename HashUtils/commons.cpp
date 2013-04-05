#include "commons.h"
#include "databaseserver.h"
#include <QtCore>
#include <QtGui>
#include <QtWebKit/QtWebKit>

#define CRORE 10000000
#define LACK 100000
#define THOUSAND 1000
#define HUNDRED 100

Commons::Commons()
{
}

QString Commons::getAdminPassword()
{
    DatabaseServer *server = new DatabaseServer;
    QString password = server->getSingleResult("select Value from Details where Field='Administrator'");
    delete server;
    return password;
}

void Commons::setAdminPassword(QString password)
{
    DatabaseServer *server = new DatabaseServer;
    server->getSingleResult("update Details set Value='" + password + "' where Field='Administrator'");
    delete server;
}

QString Commons::getSalesPassword()
{
    DatabaseServer *server = new DatabaseServer;
    QString password = server->getSingleResult("select Value from Details where Field='Sales'");
    delete server;
    return password;
}

QString Commons::getHeaderWithAddress()
{
    DatabaseServer server;
    QString header;
    header = "<center><b><font size=5>";
    header += server.getSingleResult("select Value from Details where Field = 'Name'") + "</b></font>";
    header += "<br><font size=3><b>" + server.getSingleResult("select Value from Details where Field= 'Address'") + "</b>";
    header += "<br><font size=3><b>Phone No: " + server.getSingleResult("select Value from Details where Field= 'Mobile'") + "</b></center>";
    header += "<br><b>Tin No: " + server.getSingleResult("select Value from Details where Field= 'Tin'") + "</b></font>";

    return header;
}

QString Commons::getHeaderFromTable()
{
    DatabaseServer server;
    QString header;
    header = "<center><b><font size=5>";
    header += server.getSingleResult("select Value from Details where Field = 'Name'") + "</b></font>";
    header += "<br><font size=3><b>" + server.getSingleResult("select Value from Details where Field= 'Address'") + "</b>";
    header += "<fontsize=3><br><b>Phone No: " + server.getSingleResult("select Value from Details where Field= 'Mobile'") + "</b></font>";
    header += "</center><b>Tin No: " + server.getSingleResult("select Value from Details where Field= 'Tin'") + "</b><br><b>Invoice: " + server.getSingleResult("select Value from Details where Field='Invoice'") + "</b></font>";
    return header;
}

QString Commons::getHeaderFromTableEstimate()
{
    DatabaseServer server;
    QString header;
    header = "<center><b><font size=5>";
    header += server.getSingleResult("select Value from Details where Field = 'Name'") + "</b></font>";
    header += "<br><font size=4><b>" + server.getSingleResult("select Value from Details where Field= 'Address'") + "</b>";
    header += "<font><br><b>Phone No: " + server.getSingleResult("select Value from Details where Field= 'Mobile'") + "</b></font>";
    header += "</center><b>Tin No: " + server.getSingleResult("select Value from Details where Field= 'Tin'") + "</b><br><b>Estimate: " + server.getSingleResult("select Value from Details where Field='Estimate'") + "</b></font>";
    return header;
}

QString Commons::getShopName()
{
    DatabaseServer server;
    QString value = server.getSingleResult("select Value from Details where Field = 'Name'");
    return value;
}

QString Commons::getShopAddress()
{
    DatabaseServer server;
    QString value = server.getSingleResult("select Value from Details where Field = 'Address'");
    return value;
}

QString Commons::getMobileNo()
{
    DatabaseServer server;
    QString value = server.getSingleResult("select Value from Details where Field = 'Mobile'");
    return value;
}

QString Commons::getTinNo()
{
    DatabaseServer server;
    QString value = server.getSingleResult("select Value from Details where Field = 'Tin'");
    return value;
}

QString Commons::getCommaSeperatedValue(QString value)
{
    int end = ( value.indexOf(".") >= 0) ? value.indexOf(".") : value.size();
    if(end >3)
        value.insert(end - 3, ",");
    for(int i = 5 , j=0; i < end; i = i + 2, j++)
        value.insert(end - i - j, ",");
    return value;
}

QString Commons::numberToWords(int num)
{
    if( num < 0)
    {
        QString number = "Negetive " + numberToWords(-num);
        return number;
    }

    switch(num)
    {
    case 0: return "Zero";
    case 1: return "One";
    case 2: return "Two";
    case 3: return "Three";
    case 4: return "Four";
    case 5: return "Five";
    case 6: return "Six";
    case 7: return "Seven";
    case 8: return "Eight";
    case 9: return "Nine";
    case 10: return "Ten";
    case 11: return "Eleven";
    case 12: return "Twelve";
    case 13: return "Thirteen";
    case 14: return "Fourteen";
    case 15: return "Fifteen";
    case 16: return "Sixteen";
    case 17: return "Seventeen";
    case 18: return "Eighteen";
    case 19: return "Nineteen";
    case 20: return "Twenty";
    case 30: return "Thirty";
    case 40: return "Fourty";
    case 50: return "Fifty";
    case 60: return "Sixty";
    case 70: return "Seventeen";
    case 80: return "Eighty";
    case 90: return "Ninety";
    default:
        {
            bool flag = false;
            QString number = "";

            if( num >= CRORE)
            {
                number += numberToWords(num / CRORE) + " Crore ";
                num = num % CRORE;
                flag = true;
            }
            if( num >= LACK)
            {
                number += numberToWords(num / LACK) + " Lack ";
                num = num % LACK;
                flag = true;
            }
            if( num >= THOUSAND)
            {
                number += numberToWords(num / THOUSAND) + " Thousand ";
                num = num % THOUSAND;
                flag = true;
            }
            if( num >= HUNDRED)
            {
                number += numberToWords(num / HUNDRED) + " Hundred ";
                num = num % HUNDRED;
                flag = true;
            }
            if( num > 20)
            {
                if(flag)
                    number += " And ";
                number += numberToWords(num - num % 10) + " " + ((num % 10 > 0)? numberToWords( num % 10): "");
            }
            else if(num > 0)
            {
                if(flag)
                    number += " And ";
                number += numberToWords(num);
            }
            return number;
        }
    }
    return "";
}

void Commons::setNextInvoice()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select Value from Details where Field='Invoice'");

    do
    {
        QString inCurr = server.getSingleResult("select distinct InvoiceNo from Invoice where InvoiceNo='" + inNo + "';");
        if( inNo == inCurr)
            inNo = QString::number(inNo.toInt() + 1);
        else
        {
            server.executeQuery("update Details set Value ='" + inNo + "' where Field='Invoice'");
            return;
        }
    }while(true);
}

void Commons::setNextPurchaseInvoice()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select Value from Details where Field='StockInvoice'");

    do
    {
        QString inCurr = server.getSingleResult("select distinct InvoiceNo from StockInvoice where InvoiceNo='" + inNo + "';");
        if( inNo == inCurr)
            inNo = QString::number(inNo.toInt() + 1);
        else
        {
            server.executeQuery("update Details set Value ='" + inNo + "' where Field='StockInvoice'");
            return;
        }
    }while(true);
}

QString Commons::getInvoiceNo()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select Value from Details where Field='Invoice'");
    return inNo;
}

QString Commons::getPurchaseInvoiceNo()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select Value from Details where Field='StockInvoice'");
    return inNo;
}

int Commons::getLargestInvoiceNo()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select max(InvoiceNo) from Invoice");
    return inNo.toInt();
}

int Commons::getLargestPurchaseNo()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select max(InvoiceNo) from StockInvoice");
    return inNo.toInt();
}

QString Commons::getEstimateNo()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select Value from Details where Field='Estimate'");
    return inNo;
}

int Commons::getLargestEstimateNo()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select max(EstimateNo) from Estimate");
    return inNo.toInt();
}

int Commons::getSmallestEstimateNo()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select min(EstimateNo) from Estimate");
    return inNo.toInt();
}

void Commons::setNextEstimate()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select Value from Details where Field='Estimate'");

    do
    {
        QString inCurr = server.getSingleResult("select distinct EstimateNo from Estimate where EstimateNo='" + inNo + "';");
        if( inNo == inCurr)
            inNo = QString::number(inNo.toInt() + 1);
        else
        {
            server.executeQuery("update Details set Value ='" + inNo + "' where Field='Estimate'");
            return;
        }
    }while(true);
}

int Commons::getSmallestInvoiceNo()
{
    DatabaseServer server;
    QString inNo = server.getSingleResult("select min(InvoiceNo) from Invoice");
    return inNo.toInt();
}

void Commons::printHTML(QString htmlContent)
{
    QPrinter *printer = new QPrinter;
    qDebug()<<"Default printer: "<<QPrinterInfo::defaultPrinter().printerName();
    QTextDocument *document = new QTextDocument();
    document->setTextWidth(document->idealWidth());
    document->setHtml(htmlContent);
    document->print(printer);
}

void Commons::printText(QString content)
{
    QPrinter *printer = new QPrinter;
    qDebug()<<"Default printer: "<<QPrinterInfo::defaultPrinter().printerName();
    QTextDocument *document = new QTextDocument();
    document->setTextWidth(document->idealWidth());
    document->setPlainText(content);
    document->print(printer);
}

void Commons::openFileOnDefaultApplication(QString filename)
{
    QDesktopServices::openUrl(QUrl(filename,  QUrl::TolerantMode));
}

void Commons::htmlToPDF(QString filename, QString htmlContent)
{
    QWebView *webView = new QWebView;
    webView->setHtml(htmlContent);
    QPrinter *printer = new QPrinter;
    printer->setResolution (400);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName(filename);
    printer->setPaperSize(QPrinter::A4);
    webView->print(printer);
}

void Commons::plainTextToPDF(QString filename, QString content)
{
    QPrinter *printer = new QPrinter;
    printer->setResolution (400);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName(filename);
    printer->setPaperSize(QPrinter::A4);

    QTextDocument *document = new QTextDocument();
    document->setTextWidth(document->idealWidth());
    document->setPlainText(content);
    document->print(printer);
}

void Commons::saveFile(QString filename, QString content)
{
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    out<<content;

    file.close();
}

QString Commons::modifiedText(QString text, int length)
{
    QString retText;

    for(int i = 0; i < length; i++)
    {
        if(i < text.size())
            retText += text.at(i);
        else
            retText += " ";
    }
    return retText;
}

QString Commons::getNbsps(int num)
{
    QString nbsps;
    for(int i=0; i < num; i++)
        nbsps += "&nbsp;";
    return nbsps;
}

QString Commons::alignTextCenter(QString text, int length)
{
    QString retText;
    if(length > text.size())
    {
        int pre = (length - text.size()) / 2;
        for(int i = 0; i <= pre; i++)
            retText += " ";
        retText += text;
        for(int i = 0; i <= pre; i++)
            retText += " ";
    }
    else
    {
        retText = text;
    }
    return retText;
}

QString Commons::alignTextRight(QString text, int length)
{
    QString retText;
    if(length > text.size())
    {
        int pre = length - text.size();
        for(int i = 0; i <= pre; i++)
            retText += " ";
        retText += text;
    }
    else
    {
        retText = text;
    }
    return retText;
}

QString Commons::insertNbspInBetween(QString word, int num)
{
    QString newWord;

    for(int i = 0; i < word.size(); i++)
    {
        for(int j = 0; j < num; j++)
        {
            newWord += "&nbsp;";
        }
        newWord += word.at(i);
    }
    return newWord;
}

void Commons::cancelInvoice(QString invoiceNo)
{
    DatabaseServer server;
    QStringList data = server.getMultiListResult("select CommodityId, Quantity from Invoice where InvoiceNo=" + invoiceNo);
    for(int i = 0; i < data.size(); i++)
    {
        QStringList values = data.at(i).split("\n");
        server.executeQuery("update Commodity set Quantity = Quantity + " + values.at(1) + " where Id = '" + values.at(0) + "'");
        server.executeQuery("delete from Invoice where InvoiceNo = " + invoiceNo);
    }
}
