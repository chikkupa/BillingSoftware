#ifndef TABLECONFIGURATION_H
#define TABLECONFIGURATION_H

#include <QtCore>

class TableConfiguration
{
public:
    TableConfiguration();

    static bool getCheckStockStatus();
    static bool getReturnItemStatus();
};

#endif // TABLECONFIGURATION_H
