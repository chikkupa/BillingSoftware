#include "printmodule.h"
#include <QPrinter>
#include <QTextDocument>
#include "printviewdialog.h"

PrintModule::PrintModule()
{
    directory = "";
    filename = "Bill.html";
    previewMode = false;
    noCopies = 1;
    webView = new QWebView;

    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(printFile()));
}

void PrintModule::setPreviewMode(bool mode)
{
    previewMode = mode;
}

void PrintModule::setNoOfCopies(int copies)
{
    noCopies = copies;
}

void PrintModule::printBillHtml(QStringList invoiceData, QStringList customerDetails, QStringList table, QStringList summary)
{
    QString format = getHtmlBillFormat();

    QString script;

    if(invoiceData.size() > 0)
    {
        script = "addDetails('invoiceNo',' " + invoiceData.at(0) + "');";
        script += "\naddDetails('date',' " + invoiceData.at(1) + "');";
        script += "\naddDetails('name',' " + customerDetails.at(0) + "');";
        script += "\naddDetails('address',' " + customerDetails.at(1) + "');";
        script += "\naddDetails('mobile',' " + customerDetails.at(2) + "');";
        script += "\naddDetails('phoneNo',' " + customerDetails.at(3) + "');";
        script += "\naddDetails('email',' " + customerDetails.at(4) + "');";
        script += "\naddDetails('gross',' " + summary.at(0) + "');";
        script += "\naddDetails('vat',' " + summary.at(1) + "');";
        script += "\naddDetails('cess',' " + summary.at(2) + "');";
        script += "\naddDetails('amount',' " + summary.at(3) + "');";
        script += "\naddDetails('amountWords',' " + summary.at(4) + "');";
        script += "\naddDetails('payment',' " + summary.at(5) + "');";
        script += "\naddDetails('balance',' " + summary.at(6) + "');";
    }
    for(int i = 0; i < table.size(); i++)
    {
        script += "\naddTableItem(";
        QStringList column = table.at(i).split("\n");
        script += "'" + column.at(0) + "'";
        for(int j = 1; j < column.size(); j++)
        {
            script += ",'" + column.at(j) + "'";
        }
        script += ");";
    }
    format = format.replace("#details#", script);
//    format = format.replace("#invoiceNo#", invoiceData.at(0));
//    format = format.replace("#date#", invoiceData.at(1));
//    format = format.replace("#name#", customerDetails.at(0));
//    format = format.replace("#address#", customerDetails.at(1));
//    format = format.replace("#mobile#", customerDetails.at(2));
//    format = format.replace("#phoneNo#", customerDetails.at(3));
//    format = format.replace("#email#", customerDetails.at(4));
//    format = format.replace("#table#", getHtmlTable(table));
//    format = format.replace("#gross#", summary.at(0));
//    format = format.replace("#vat#", summary.at(1));
//    format = format.replace("#cess#", summary.at(2));
//    format = format.replace("#amount#", summary.at(3));
//    format = format.replace("#amountwords#", summary.at(4));

    if(previewMode)
    {
        PrintViewDialog dialog;
        if(dialog.setwebView(format))
        {
            printHTML(format);
        }
    }
    else
        printHTML(format);
}

void PrintModule::printReportHtml(QStringList reportData, QStringList table)
{
    QString format = getHtmlBillFormat();

    QString script;

    for(int i = 0; i < table.size(); i++)
    {
        script += "\naddTableItem(";
        QStringList column = table.at(i).split("\n");
        script += "'" + column.at(0) + "'";
        for(int j = 1; j < column.size(); j++)
        {
            script += ",'" + column.at(j) + "'";
        }
        script += ");";
    }
    for(int i = 0; i < reportData.size(); i++)
    {
        script += "\naddDetails('" + QString::number(i) + "', '" + reportData.at(i) + "')";
    }
    format = format.replace("#details#", script);

    if(previewMode)
    {
        PrintViewDialog dialog;
        if(dialog.setwebView(format, directory))
        {
            printHTML(format);
        }
    }
    else
        printHTML(format);
}

void PrintModule::printChellanHtml(QStringList invoiceData, QStringList customerDetails, QStringList table, QStringList summary, QStringList chellanDetails)
{
    QString format;// = getHtmlBillFormat("ChellanInvoice.html");

    format = format.replace("#deliveryNote#", chellanDetails.at(0));
    format = format.replace("#modeOfPayment#", chellanDetails.at(1));
    format = format.replace("#supplierRef#", chellanDetails.at(2));
    format = format.replace("#otherRef#", chellanDetails.at(3));
    format = format.replace("#orderNo#", chellanDetails.at(4));
    format = format.replace("#orderDate#", chellanDetails.at(5));
    format = format.replace("#despatchNo#", chellanDetails.at(6));
    format = format.replace("#despatchDate#", chellanDetails.at(7));
    format = format.replace("#despatchedThrough#", chellanDetails.at(8));
    format = format.replace("#destination#", chellanDetails.at(9));
    format = format.replace("#consignee#", chellanDetails.at(10));
    format = format.replace("#buyer", chellanDetails.at(11));
    format = format.replace("#termsOfDelivery#", chellanDetails.at(12));

    format = format.replace("#invoiceNo#", invoiceData.at(0));
    format = format.replace("#date#", invoiceData.at(1));
    format = format.replace("#name#", customerDetails.at(0));
    format = format.replace("#table#", getHtmlTable(table));
    format = format.replace("#gross#", summary.at(0));
    format = format.replace("#vat#", summary.at(1));
    format = format.replace("#cess#", summary.at(2));
    format = format.replace("#amount#", summary.at(3));
    format = format.replace("#amountwords#", summary.at(4));

    if(previewMode)
    {
        PrintViewDialog dialog;
        if(dialog.setwebView(format))
        {
            printHTML(format);
        }
    }
    else
        printHTML(format);
}

QString PrintModule::getHtmlBillFormat()
{
    QFile file(directory + filename);
    QString content;

    if(!file.open(QIODevice::ReadOnly))
    {
        return content;
    }
    QTextStream in(&file);
    content = in.readAll();
    return content;
}

QString PrintModule::getHtmlTable(QStringList table)
{
    QString htmlTable;
    for(int i = 0; i < table.size(); i++)
    {
        htmlTable += "<tr>";
        QStringList column = table.at(i).split("\n");

        for(int j = 0; j < column.size(); j++)
        {
            htmlTable += "<td>" + column.at(j) + "</td>";
        }
    }

    return htmlTable;
}

void PrintModule::setFilename(QString filename)
{
    this->filename = filename;
}

void PrintModule::setDirecory(QString directory)
{
    this->directory = directory + "/";
}

void PrintModule::printHTML(QString htmlContent)
{
    QString filename = directory + "Sample.html";
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Error opening Sample.htnl!!";
        return;
    }

    QTextStream out(&file);
    out<<htmlContent;
    file.close();

    webView->load(QUrl(filename));
    qDebug()<<filename;
    //QTextDocument doc;
	//doc.setHtml(...); // or populate using QTextCursor
//    doc.drawContents(painter);
//    QTextDocument *document = new QTextDocument();
//    document->setTextWidth(document->idealWidth());
//    document->setHtml(htmlContent);
                     //    document->print(printer);
}

void PrintModule::printFile()
{
    qDebug()<<"Print File";
    QPrinter *printer = new QPrinter;
//    printer->setOutputFormat(QPrinter::PdfFormat);
//    printer->setOutputFileName("Bill.pdf");

    for(int i = 0; i < noCopies; i++)
        webView->print(printer);
}
