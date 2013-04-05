#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "adminhomewidget.h"
#include "invoicewidget.h"
#include "dailysalesreportwidget.h"
#include "todaysitemsaleswidget.h"
#include "managestockwidget.h"
#include "stockpurchaseinvoicewidget.h"
#include "oldpurchaseinvoicewidget.h"
#include "oldinvoiceswidget.h"
#include "allinvoices.h"
#include "estimatewidget.h"
#include "oldestimates.h"
#include "itemestimatewidget.h"
#include "salesdetailswidget.h"
#include "purchasereportwidget.h"
#include "purchaseditemwidget.h"
#include "accountswidget.h"
#include "historydsrwidget.h"
#include "historyitemsaleswidget.h"
#include "historyinvoicewidget.h"

class QTimerEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool loginStatus;
    int updateTimer;
    int widgetHeight;
    int widgetWidth;

    QMenuBar *menubar;
    QMenu *menuAdministrator;
    QMenu *menuStock;
    QMenu *menuInvoice;
    QMenu *menuEstimate;
    QMenu *menuDealer;
    QMenu *menuAccounts;
    QMenu *menuReports;
    QMenu *menuSettings;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    AdminHomeWidget *adminHome;
    InvoiceWidget *invoice;
    DailySalesReportWidget *dailyReport;
    TodaysItemSalesWidget *itemSales;
    ManageStockWidget *manageStock;
    StockPurchaseInvoiceWidget *purchaseInvoice;
    OldPurchaseInvoiceWidget *oldPurchaseInvoice;
    OldInvoicesWidget *oldInvoice;
    AllInvoices *allInvoices;
    EstimateWidget *estimate;
    OldEstimates *oldEstimate;
    ItemEstimateWidget *itemEstimate;
    SalesDetailsWidget *salesDetails;
    AccountsWidget *accounts;
    PurchaseReportWidget *purchaseReport;
    PurchasedItemWidget *purchasedItems;
    HistoryDSRWidget *historyDsr;
    HistoryItemSalesWidget *historyItemSales;
    HistoryInvoiceWidget *historyinvoice;

    void timerEvent(QTimerEvent *e);

protected: signals:
    void shutdown();

private slots:
    void getAdminHome();
    void getItemSales();
    void getDailySalesReport();
    void getItemSalesReport();
    void getChangePasswordDialog();
    void getBulkStockUpdationDialog();
    void getStockPurchaseInvoice();
    void getOldStockPurchaseInvoice();
    void getStockUpdationDialog();
    void getAddNewStockDialog();
    void getDeleteStockDialog();
    void getUpdateStockDialog();
    void getFullScreen();
    void getManageStockWidget();
    void getCheckStockDialog();
    void getInvoice();
    void getSetInvoiceDialog();
    void cancelInvoice();
    void getOldInvoice();
    void getAllInvoice();
    void getEstimate();
    void getOldEstimates();
    void getSetEstimateDialog();
    void cancelEstimate();
    void getItemEstimate();
    void getSalesDetails();
    void getAccountsWidget();
    void getPurchaseReport();
    void getPurchasedItems();
    void getHistoryInvoice();
    void getHistoryDsrWidget();
    void getHistoryItemSales();
    void getConfiguration();
    void getDeleteDataAct();
    void getBackup();
    void shortcuts();
    void about();
    void refresh();
    void restart();
    void hideAllWidgets();
    void getSalesMode();
    void login();
};

#endif // MAINWINDOW_H
