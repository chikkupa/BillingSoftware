#ifndef COMMONS_H
#define COMMONS_H

#include <QtCore>

class Commons
{
    public:
        Commons();
        static QString getAdminPassword();
        static void setAdminPassword(QString password);
        static QString getSalesPassword();
        static QString getHeaderWithAddress();
        static QString getHeaderFromTable();
        static QString getHeaderFromTableEstimate();
        static QString getShopName();
        static QString getShopAddress();
        static QString getMobileNo();
        static QString getTinNo();
        static QString getCommaSeperatedValue(QString);
        static QString numberToWords(int);
        static void setNextInvoice();
        static void setNextPurchaseInvoice();
        static QString getInvoiceNo();
        static QString getPurchaseInvoiceNo();
        static void setNextEstimate();
        static QString getEstimateNo();
        static int getLargestInvoiceNo();
        static int getLargestPurchaseNo();
        static int getSmallestEstimateNo();
        static int getLargestEstimateNo();
        static int getSmallestInvoiceNo();
        static void printHTML(QString);
        static void openFileOnDefaultApplication(QString);
        static void htmlToPDF(QString, QString);
        static void plainTextToPDF(QString, QString);
        static void printText(QString);
        static void saveFile(QString, QString);
        static QString modifiedText(QString, int);
        static QString getNbsps(int);
        static QString alignTextCenter(QString, int);
        static QString alignTextRight(QString, int);
        static QString insertNbspInBetween(QString, int);
        static void cancelInvoice(QString);
};

#endif // COMMONS_H
