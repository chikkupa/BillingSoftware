#include "mainwindow.h"
#include <QtGui>
#include <QtSql>
#include "databaseserver.h"
#include "loginwindow.h"
#include "itemsalesreport.h"
#include "changepassworddialog.h"
#include "bulkstockupdationdialog.h"
#include "stockupdationdialog.h"
#include "addnewstockdialog.h"
#include "deletestockdialog.h"
#include "updatestockdetailsdialog.h"
#include "checkstockdialog.h"
#include "setinvoicedialog.h"
#include "setestimatedialog.h"
#include "getinvoicenodialog.h"
#include "getestimatenodialog.h"
#include "cancelestimatedialog.h"
#include "cancelinvoicedialog.h"
#include "globalcache.h"
#include "backup.h"
#include "configurationdialog.h"
#include "deleteDataDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    GlobalCache *globalCache = new GlobalCache();
    loginStatus = false;

    updateTimer = startTimer(100);

    QTimerEvent *e= new QTimerEvent(updateTimer);

    setWindowTitle("#precIsioN Billing Software 1.2");

    /* Setting height and width properties */
    QDesktopWidget *desktop = QApplication::desktop();
    int width = desktop->width();
    int height = desktop->height();
    GlobalCache::setScreenWidth(width);
    GlobalCache::setScreenHeight(height);
    resize(width/2, height/2);
    int sideWidth = 10; //width/48;
    int sideHeight = (height-50)/14;
    widgetWidth = width - 20; //sideWidth *46;
    widgetHeight = sideHeight * 14;

    /* Creating menu bar and status bar */
    menubar = new QMenuBar(this);
    setMenuBar(menubar);

    menuAdministrator = new QMenu(menubar);
    menuAdministrator->setTitle("Administrator");
    menubar->addMenu(menuAdministrator);

    QAction *homeAct = new QAction(("&Home"), this);
    homeAct->setShortcut(QKeySequence(tr("Ctrl+H")));
    menuAdministrator->addAction(homeAct);
    menuAdministrator->addSeparator();
    QAction *changePasswordAct = new QAction("Change Password", this);
    menuAdministrator->addAction(changePasswordAct);
    QAction *refreshAct = new QAction(("&Refresh"), this);
    refreshAct->setShortcut(QKeySequence(tr("Ctrl+R")));
    menuAdministrator->addAction(refreshAct);
    QAction *fullScreenAct = new QAction(("&Full Screen"), this);
    fullScreenAct->setShortcut(Qt::Key_F11);
    menuAdministrator->addAction(fullScreenAct);
    QAction *restartAct = new QAction("Restart", this);
    restartAct->setShortcut(QKeySequence((tr("Shift+Ctrl+X"))));
    menuAdministrator->addAction(restartAct);
    QAction *quitAct = new QAction(("Quit Application"), this);
    quitAct->setShortcut(QKeySequence(tr("Ctrl+X")));
    menuAdministrator->addAction(quitAct);

    menuStock = new QMenu(menubar);
    menuStock->setTitle("Stock");
    menubar->addMenu(menuStock);

    QAction *manageStockAct = new QAction(("Manage Stock"), this);
    manageStockAct->setShortcut(QKeySequence(tr("Ctrl+M")));
    menuStock->addAction(manageStockAct);
    QAction *bulkStockUpdationAct = new QAction("Bulk Stock Updation", this);
    bulkStockUpdationAct->setShortcut(QKeySequence(tr("Ctrl+U")));
    menuStock->addAction(bulkStockUpdationAct);
    menuStock->addSeparator();
    QAction *stockPruchaseInvoiceAct = new QAction(("Stock Purchase Invoice"), this);
    menuStock->addAction(stockPruchaseInvoiceAct);
    QAction *oldStockPurchaseInvoiceAct = new QAction(("Old Stock Purchase Invoice"), this);
    menuStock->addAction(oldStockPurchaseInvoiceAct);
    menuStock->addSeparator();
    QAction *stockUpdationAct = new QAction(("Single Stock Updation"), this);
    menuStock->addAction(stockUpdationAct);
    menuStock->addSeparator();
    QAction *addNewStockAct = new QAction(("Add New Stock"), this);
    menuStock->addAction(addNewStockAct);
    QAction *deleteStockact = new QAction(("Remove Stock"), this);
    menuStock->addAction(deleteStockact);
    QAction *updateStockAct = new QAction(("Edit Stock Details"), this);
    menuStock->addAction(updateStockAct);
    menuStock->addSeparator();
    QAction *checkStockAct = new QAction("Check Stock", this);
    checkStockAct->setShortcut(QKeySequence("Ctrl+F"));
    menuStock->addAction(checkStockAct);

    menuInvoice = new QMenu(menubar);
    menuInvoice->setTitle("Invoice");
    menubar->addMenu(menuInvoice);

    QAction *invoiceAct = new QAction(("&New Invoice"), this);
    invoiceAct->setShortcut(QKeySequence(tr("Ctrl+N")));
    menuInvoice->addAction(invoiceAct);
    QAction *setInvoiceAct = new QAction(("Set Invoice No"), this);
    menuInvoice->addAction(setInvoiceAct);
    QAction *cancelInvoiceAct = new QAction(("Cancel Invoice"), this);
    menuInvoice->addAction(cancelInvoiceAct);
    QAction *oldInvoiceAct = new QAction(("Old Invoices"), this);
    menuInvoice->addAction(oldInvoiceAct);

    menuEstimate = new QMenu(menubar);
    menuEstimate->setTitle("Estimate");
    menubar->addMenu(menuEstimate);

    QAction *estimateAct = new QAction(("&New Estimate"), this);
    estimateAct->setShortcut(QKeySequence(tr("Ctrl+E")));
    menuEstimate->addAction(estimateAct);
    QAction *setEstimateAct = new QAction(("Set Estimate No"), this);
    menuEstimate->addAction(setEstimateAct);
    QAction *cancelEstimateAct = new QAction(("Cancel Estimate"), this);
    menuEstimate->addAction(cancelEstimateAct);
    QAction *oldEstimateAct = new QAction(("Old Estimates"), this);
    menuEstimate->addAction(oldEstimateAct);
    menuEstimate->addSeparator();
    QAction *itemEstimateAct = new QAction("Item Estimates", this);
    menuEstimate->addAction(itemEstimateAct);


    menuDealer = new QMenu(menubar);
    menuDealer->setTitle("Dealer");
//    menubar->addMenu(menuDealer);

    QAction *dealerHomeAct = new QAction(("&Dealer Home"), this);
    dealerHomeAct->setShortcut(QKeySequence(tr("Ctrl+D")));
    menuDealer->addAction(dealerHomeAct);
    QAction *salesDetailsAct = new QAction(("Sales De&tais"), this);
    salesDetailsAct->setShortcut(QKeySequence(tr("Ctrl+T")));
    menuDealer->addAction(salesDetailsAct);
    QAction *addNewDealerAct = new QAction(("Add New Dealer"), this);
    menuDealer->addAction(addNewDealerAct);
    QAction *deleteDealerAct = new QAction(("Delete Dealer"), this);
    menuDealer->addAction(deleteDealerAct);
    QAction *updateDealerAct = new QAction(("Edit Dealer Details"), this);
    menuDealer->addAction(updateDealerAct);

    menuAccounts = new QMenu(menubar);
    menuAccounts->setTitle("Accounts");
    menubar->addMenu(menuAccounts);

    QAction *accountsAct = new QAction(("Accounts"), this);
    accountsAct->setShortcut(QKeySequence(tr("Ctrl+A")));
    menuAccounts->addAction(accountsAct);

    menuReports = new QMenu(menubar);
    menuReports->setTitle("Reports");
    menubar->addMenu(menuReports);

    QAction *todaysItemSalesAct = new QAction(("Today's &Item Sales"), this);
    todaysItemSalesAct->setShortcut(QKeySequence(tr("Ctrl+I")));
    menuReports->addAction(todaysItemSalesAct);
    QAction *dailyReportAct = new QAction(("Daily Sales &Report"), this);
    dailyReportAct->setShortcut(QKeySequence(tr("Ctrl+R")));
    menuReports->addAction(dailyReportAct);
    QAction *itemSalesReportAct = new QAction("Selected Item Sales Report", this);
    menuReports->addAction(itemSalesReportAct);
    QAction *historyItemSalesAct = new QAction(("History Item Sales"), this);
    menuReports->addAction(historyItemSalesAct);
    menuReports->addSeparator();
    QAction *purchaseReportAct = new QAction("Purchase Report", this);
    menuReports->addAction(purchaseReportAct);
    QAction *purchaseItemsAct = new QAction("Purchased Item Report", this);
    menuReports->addAction(purchaseItemsAct);

    menuSettings = new QMenu(menubar);
    menuSettings->setTitle("Settings");
    menubar->addMenu(menuSettings);

    QAction *configurationAct = new QAction(("Configure Product"), this);
    menuSettings->addAction(configurationAct);
    QAction *deleteDataAct = new QAction("Clear Data", this);
    menuSettings->addAction(deleteDataAct);
    QAction *backupAct = new QAction(("Backup"), this);
    menuSettings->addAction(backupAct);

    menuHelp = new QMenu(menubar);
    menuHelp->setTitle("Help");
    menubar->addMenu(menuHelp);

    QAction *shortcutAct = new QAction(("Shorcuts Used"), this);
    menuHelp->addAction(shortcutAct);
    QAction *aboutAct = new QAction(("About"), this);
    menuHelp->addAction(aboutAct);

    adminHome = new AdminHomeWidget(widgetWidth, this);
    adminHome->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    manageStock = new ManageStockWidget(widgetWidth, this);
    manageStock->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    purchaseInvoice = new StockPurchaseInvoiceWidget(widgetWidth, this);
    purchaseInvoice->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    oldPurchaseInvoice = new OldPurchaseInvoiceWidget(widgetWidth, this);
    oldPurchaseInvoice->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    invoice = new InvoiceWidget(widgetWidth, this);
    invoice->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    dailyReport = new DailySalesReportWidget(widgetWidth, this);
    dailyReport->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    itemSales = new TodaysItemSalesWidget(widgetWidth, this);
    itemSales->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    oldInvoice = new OldInvoicesWidget(widgetWidth, this);
    oldInvoice->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    allInvoices = new AllInvoices(widgetWidth, this);
    allInvoices->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    oldEstimate = new OldEstimates(widgetWidth, this);
    oldEstimate->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    itemEstimate = new ItemEstimateWidget(widgetWidth, this);
    itemEstimate->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    estimate = new EstimateWidget(widgetWidth, this);
    estimate->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    salesDetails = new SalesDetailsWidget(widgetWidth, this);
    salesDetails->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    accounts = new AccountsWidget(widgetWidth, this);
    accounts->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    purchaseReport = new PurchaseReportWidget(widgetWidth, this);
    purchaseReport->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    purchasedItems = new PurchasedItemWidget(widgetWidth, this);
    purchasedItems->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    historyDsr = new HistoryDSRWidget(widgetWidth, this);
    historyDsr->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    historyItemSales = new HistoryItemSalesWidget(widgetWidth, this);
    historyItemSales->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);
    historyinvoice = new HistoryInvoiceWidget(widgetWidth, this);
    historyinvoice->setGeometry(sideWidth, 50, widgetWidth, widgetHeight - 50);

    /* Main Window setup */

    connect( homeAct, SIGNAL(triggered()), this, SLOT(getAdminHome()));
    connect( todaysItemSalesAct, SIGNAL(triggered()), this, SLOT(getItemSales()));
    connect( dailyReportAct, SIGNAL(triggered()), this, SLOT(getDailySalesReport()));
    connect( itemSalesReportAct, SIGNAL(triggered()), this, SLOT(getItemSalesReport()));
    connect( bulkStockUpdationAct, SIGNAL(triggered()), this, SLOT(getBulkStockUpdationDialog()));
    connect( stockUpdationAct, SIGNAL(triggered()), this, SLOT(getStockUpdationDialog()));
    connect( addNewStockAct, SIGNAL(triggered()), this, SLOT(getAddNewStockDialog()));
    connect( deleteStockact, SIGNAL(triggered()), this, SLOT(getDeleteStockDialog()));
    connect( updateStockAct, SIGNAL(triggered()), this, SLOT(getUpdateStockDialog()));
    connect( checkStockAct, SIGNAL(triggered()), this, SLOT(getCheckStockDialog()));
    connect( changePasswordAct, SIGNAL(triggered()), this, SLOT(getChangePasswordDialog()));
    connect( refreshAct, SIGNAL(triggered()), this, SLOT(refresh()));
    connect( fullScreenAct, SIGNAL(triggered()), this, SLOT(getFullScreen()));
    connect( restartAct, SIGNAL(triggered()), this, SLOT(restart()));
    connect( quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect( manageStockAct, SIGNAL(triggered()), this, SLOT(getManageStockWidget()));
    connect( stockPruchaseInvoiceAct, SIGNAL(triggered()), this, SLOT(getStockPurchaseInvoice()));
    connect( oldStockPurchaseInvoiceAct, SIGNAL(triggered()), this, SLOT(getOldStockPurchaseInvoice()));
    connect( invoiceAct, SIGNAL(triggered()), this, SLOT(getInvoice()));
    connect( setInvoiceAct, SIGNAL(triggered()), this, SLOT(getSetInvoiceDialog()));
    connect( cancelInvoiceAct, SIGNAL(triggered()), this, SLOT(cancelInvoice()));
    connect( oldInvoiceAct, SIGNAL(triggered()), this, SLOT(getOldInvoice()));
    connect( estimateAct, SIGNAL(triggered()), this, SLOT(getEstimate()));
    connect( setEstimateAct, SIGNAL(triggered()), this, SLOT(getSetEstimateDialog()));
    connect( cancelEstimateAct, SIGNAL(triggered()), this, SLOT(cancelEstimate()));
    connect( oldEstimateAct, SIGNAL(triggered()), this, SLOT(getOldEstimates()));
    connect( itemEstimateAct, SIGNAL(triggered()), this, SLOT(getItemEstimate()));
    connect( salesDetailsAct, SIGNAL(triggered()), this, SLOT(getSalesDetails()));
    connect( accountsAct, SIGNAL(triggered()), this, SLOT(getAccountsWidget()));
    connect( purchaseReportAct, SIGNAL(triggered()), this, SLOT(getPurchaseReport()));
    connect( purchaseItemsAct, SIGNAL(triggered()), this, SLOT(getPurchasedItems()));
    connect( historyItemSalesAct, SIGNAL(triggered()), this, SLOT(getHistoryItemSales()));
    connect( configurationAct, SIGNAL(triggered()), this, SLOT(getConfiguration()));
    connect( deleteDataAct, SIGNAL(triggered()), this, SLOT(getDeleteDataAct()));
    connect( backupAct, SIGNAL(triggered()), this, SLOT(getBackup()));
    connect( shortcutAct, SIGNAL(triggered()), this, SLOT(shortcuts()));
    connect( aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));

    hideAllWidgets();
    showMinimized();
}

void MainWindow::getAdminHome()
{
    hideAllWidgets();
    adminHome->show();
    adminHome->setData();
}

void MainWindow::getItemSales()
{
    hideAllWidgets();
    itemSales->show();
    itemSales->setData(QDate::currentDate());
}

void MainWindow::getDailySalesReport()
{
    hideAllWidgets();
    dailyReport->show();
    dailyReport->setData();
}

void MainWindow::getItemSalesReport()
{
    ItemSalesReport dialog;
    dialog.getItemSales();
}

void MainWindow::getChangePasswordDialog()
{
    ChangePasswordDialog dialog;
    dialog.getPasswordDialog("");
}

void MainWindow::getBulkStockUpdationDialog()
{
    BulkStockUpdationDialog dialog;
    dialog.bulkStockUpdation();
    refresh();
}

void MainWindow::getStockPurchaseInvoice()
{
    hideAllWidgets();
    purchaseInvoice->show();
    purchaseInvoice->setData();
}

void MainWindow::getOldStockPurchaseInvoice()
{
    hideAllWidgets();
    oldPurchaseInvoice->show();
    oldPurchaseInvoice->setData();
}

void MainWindow::getStockUpdationDialog()
{
    StockUpdationDialog dialog;
    while(dialog.stockAddition());
    refresh();
}

void MainWindow::getAddNewStockDialog()
{
    AddNewStockDialog dialog;
    dialog.addNewStock();
    refresh();
}

void MainWindow::getDeleteStockDialog()
{
    deleteStockDialog dialog;
    dialog.deleteStock();
    refresh();
}

void MainWindow::getUpdateStockDialog()
{
    UpdateStockDetailsDialog dialog;
    dialog.updateStockDetails();
    refresh();
}

void MainWindow::getFullScreen()
{
    static bool screen = true;
    if(screen)
    {
    showFullScreen();
    screen = false;
    }
    else
    {
        showMaximized();
        screen = true;
    }
}

void MainWindow::getManageStockWidget()
{
    hideAllWidgets();
    manageStock->show();
    manageStock->setData();
}

void MainWindow::getCheckStockDialog()
{
    CheckStockDialog dialog;
    dialog.checkStock();
}

void MainWindow::getInvoice()
{
    hideAllWidgets();
    invoice->show();
    invoice->setData();
}

void MainWindow::getSetInvoiceDialog()
{
    setInvoiceDialog dialog;
    dialog.setInvoiceNo();
    refresh();
}

void MainWindow::cancelInvoice()
{
    CancelInvoiceDialog dialog;
    dialog.cancelInvoice();
}

void MainWindow::getOldInvoice()
{
    hideAllWidgets();
    oldInvoice->show();
    oldInvoice->setData();
}

void MainWindow::getAllInvoice()
{
    hideAllWidgets();
    allInvoices->show();
    allInvoices->setData();
}

void MainWindow::getEstimate()
{
    hideAllWidgets();
    estimate->show();
    estimate->setData();
}

void MainWindow::getSetEstimateDialog()
{
    SetEstimateDialog dialog;
    dialog.setEstimateNo();
}

void MainWindow::cancelEstimate()
{
    CancelEstimateDialog dialog;
    dialog.cancelInvoice();
}

void MainWindow::getItemEstimate()
{
    hideAllWidgets();
    itemEstimate->show();
    itemEstimate->setData();
}

void MainWindow::getOldEstimates()
{
    hideAllWidgets();
    oldEstimate->show();
    oldEstimate->setData();
}


void MainWindow::getSalesDetails()
{
    hideAllWidgets();
    salesDetails->show();
    salesDetails->setData();
}

void MainWindow::getAccountsWidget()
{
    hideAllWidgets();
    accounts->show();
    accounts->setDetails();
}

void MainWindow::getPurchaseReport()
{
    hideAllWidgets();
    purchaseReport->show();
    purchaseReport->setData();
}

void MainWindow::getPurchasedItems()
{
    hideAllWidgets();
    purchasedItems->show();
    purchasedItems->setData();
}

void MainWindow::getHistoryInvoice()
{
    hideAllWidgets();
    historyinvoice->show();
    historyinvoice->setData();
}

void MainWindow::getHistoryDsrWidget()
{
    hideAllWidgets();
    historyDsr->show();
    historyDsr->setData();
}

void MainWindow::getHistoryItemSales()
{
    hideAllWidgets();
    historyItemSales->show();
    historyItemSales->setData(QDate::currentDate());
}

void MainWindow::getConfiguration()
{
    ConfigurationDialog dialog;
    dialog.getConfiguration();
}

void MainWindow::getDeleteDataAct()
{
    DeleteDataDialog dialog;
    dialog.getDeleteDataDialog();
}

void MainWindow::getBackup()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Backup as ..."),
                                                    "Backup" + QDate::currentDate().toString("dd-MM-yy") + ".bak",
                                tr(""));
    Backup backup;
    backup.saveBackup(fileName);
}

void MainWindow::shortcuts()
{
    QTextEdit* help=new QTextEdit();
    //help->setWindowFlag(Qt::Window); //or Qt::Tool, Qt::Dialog if you like
    help->setWindowTitle("Shortcuts Used: Commodity Management Software");
    help->resize(500, 300);
    help->move((widgetWidth - 400) / 2, (widgetHeight - 300) / 2);
    help->setReadOnly(true);
    QString text;
    text = "<center><h2>Shortcuts</h2></center>";
    text += "<center><b><table><tr><td>Administrator Home: </td><td>Ctrl+H</td></tr>";
    text += "<tr><td>Daily Sales Report: </td><td>Ctrl+R</td></tr>";
    text += "<tr><td>Full Screen: </td><td>F11</td></tr>";
    text += "<tr><td>Quit: </td><td>Ctrl+X</td></tr>";
    text += "<tr><td>New Invoice: </td><td>Ctrl+N</td></tr>";
    text += "<tr><td>Add an Item </td><td>Ctrl+Space</td></tr>";
    text += "<tr><td>Remove Item </td><td>Ctrl+Alt+Space</td></tr>";
    text += "<tr><td>Remove Last Item: </td><td>Shift+Ctrl+Space</td></tr>";
    text += "<tr><td>Account Manage Stock: </td><td>Ctrl+M</td></tr>";
    text += "<tr><td>Accounts- Delete Item: </td><td>Shift+Ctrl+D</td></tr>";

    help->append(text);
    help->show();
}

void MainWindow::about()
{
    QTextEdit* help=new QTextEdit();
    help->setWindowTitle("About #precIsioN Billing Software");
    help->resize(500, 300);
    help->move((widgetWidth - 400) / 2, (widgetHeight - 300) / 2);
    help->setReadOnly(true);
    help->append("<center><h2>#precIsioN Billing Software 1.2</h2>");
    help->append("<b>Version: 1.2");
    help->append("Build Date: 04-11-2012");
    help->append("Update: 0");
    help->append("<b>Designed By: HashInclude</b>");
    help->append("Email: info@hashin.in");
    help->append("<b>www.hashin.in</b></center>");
    help->append("<center>This is a software designed to handle small or medium billing applications.</center>");
    help->show();
}

void MainWindow::refresh()
{
    if(!adminHome->isHidden())
        adminHome->setData();
    if(!manageStock->isHidden())
        manageStock->setData();
    if(!purchaseInvoice->isHidden())
        purchaseInvoice->setData();
    if(!oldPurchaseInvoice->isHidden())
        oldPurchaseInvoice->setData();
    if(!invoice->isHidden())
        invoice->setData();
    if(!dailyReport->isHidden())
        dailyReport->setData();
    if(!itemSales->isHidden())
        itemSales->setData(QDate::currentDate());
    if(!salesDetails->isHidden())
        salesDetails->setData();
    if(!oldInvoice->isHidden())
        oldInvoice->setData();
    if(!allInvoices->isHidden())
        allInvoices->setData();
    if(!estimate->isHidden())
        estimate->setData();
    if(oldEstimate->isHidden())
        oldEstimate->setData();
    if(itemEstimate->isHidden())
        itemEstimate->setData();
    if(!accounts->isHidden())
        accounts->setDetails();
    if(purchaseReport->isHidden())
        purchaseReport->setData();
    if(!purchasedItems->isHidden())
        purchasedItems->setData();
    if(!historyinvoice->isHidden())
        historyinvoice->setData();
    if(!historyDsr->isHidden())
        historyDsr->setData();
    if(!historyItemSales->isHidden())
        historyItemSales->setData(QDate::currentDate());
}

void MainWindow::restart()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::hideAllWidgets()
{
    adminHome->hide();
    manageStock->hide();
    purchaseInvoice->hide();
    oldPurchaseInvoice->hide();
    invoice->hide();
    dailyReport->hide();
    itemSales->hide();
    salesDetails->hide();
    oldInvoice->hide();
    allInvoices->hide();
    estimate->hide();
    oldEstimate->hide();
    itemEstimate->hide();
    accounts->hide();
    purchaseReport->hide();
    purchasedItems->hide();
    historyinvoice->hide();
    historyDsr->hide();
    historyItemSales->hide();
}

void MainWindow::getSalesMode()
{
    menuAdministrator->clear();
    menuAdministrator->clear();
    menuStock->clear();
    menuDealer->clear();
    menuAccounts->clear();
    menuReports->clear();
    menuSettings->clear();
    menuHelp->clear();
}

void MainWindow::login()
{
    LoginWindow login;
    QList<int> logCheck = login.checkLogin("");
    if(logCheck.at(0))
    {
        if(logCheck.at(1) == 1)
        {
            getSalesMode();
            getInvoice();
        }
        else
        {
            getAdminHome();
        }
    }
    else
    {
        QApplication::exit(0);
    }

}

MainWindow::~MainWindow()
{
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    if(!e)
        return;
    if(e->timerId() == updateTimer && !loginStatus)
    {
        loginStatus = true;
        login();
        showMaximized();
    }
}
