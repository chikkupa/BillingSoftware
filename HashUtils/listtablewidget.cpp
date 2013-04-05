#include "listtablewidget.h"
#include <QtGui>

ListTableWidget::ListTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
}
void ListTableWidget::setList(QStringList list , bool editable)
{
    try
    {
        if(!list.isEmpty())
        {
            header = list.at(0).split("\n");
            setColumnCount(header.size());
            setRowCount(list.size() -1);

            for(int i=0; i < header.size(); i++)
            {
                QTableWidgetItem *item = new QTableWidgetItem(header.at(i));
                setHorizontalHeaderItem(i, item);
            }

            for(int i=1; i < list.size(); i++)
            {
                QStringList row = list.at(i).split("\n");
                for(int j=0; j < row.size(); j++)
                {
                    QTableWidgetItem *item = new QTableWidgetItem(row.at(j));
                    setItem(i-1, j, item);
                }
            }
        }
        scrollToBottom();
        setEditable(editable);
        setSortingEnabled(true);
    }
    catch(...)
    {
        qDebug()<<"[ListTableWidget]-> [function: SetList]: Error set list";
    }
}

void ListTableWidget::set2DList(QList<QStringList> list, bool editable)
{
    if(!list.isEmpty())
    {
        header = list.at(0);
        setColumnCount(header.size());
        setRowCount(list.size() -1);
        int index = 0;

        for(int i=index; i < header.size() + index; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(header.at(i - index));
            setHorizontalHeaderItem(i, item);
        }
        for(int i=1; i < list.size(); i++)
        {
            QStringList row = list.at(i);
            for(int j=index; j < row.size() + index; j++)
            {
                QTableWidgetItem *item = new QTableWidgetItem(row.at(j - index));
                QTableWidget::setItem(i-1, j, item);
            }
        }
    }
    scrollToBottom();
    setEditable(editable);
    setSortingEnabled(true);
}

QStringList ListTableWidget::getList()
{
    QStringList list;
    QString head;
    if( columnCount() > 0)
        head = horizontalHeaderItem(0)->text();
    for(int i=1; i < columnCount(); i++)
        head += "\n" + horizontalHeaderItem(i)->text();
    list.append(head);
    for(int i=0; i< rowCount(); i++)
    {
        QString itm;
        if( columnCount() > 0)
            itm = getItem(i,0);
        for(int j=1; j < columnCount(); j++)
            itm += "\n" + getItem(i,j);
        list.append(itm);
    }
    return list;
}

QString ListTableWidget::getItem(int row, int column)
{
    if(!item(row, column)->text().isNull())
        return item(row, column)->text();
    return "";
}

void ListTableWidget::setEditable(bool flag)
{
    if(!flag)
        for(int i=0; i < rowCount(); i++)
        {
            for(int j=0; j < columnCount(); j++)
            {
                QTableWidgetItem *itm = item(i, j);
                itm->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            }
        }
}

void ListTableWidget::setEditableColumn(int column, bool editable)
{
    if(!editable)
    {
        for(int i = 0; i < rowCount(); i++)
        {
            QTableWidgetItem *itm = item(i, column);
            itm->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }
}

void ListTableWidget::addEndRow(QString row)
{
    setRowCount(rowCount() +1);
    QStringList items = row.split("\n");

    for(int i = 0; i < items.size(); i++)
    {
        QTableWidgetItem *itm = new QTableWidgetItem;
        itm->setText(items.at(i));
        setItem(rowCount()-1, i, itm);
    }
}

float ListTableWidget::getSumOfColumn(int colIndex)
{
    float sum = 0;
    for(int i=0; i < rowCount(); i++)
    {
        sum += getItem(i, colIndex).toFloat();
    }
    return sum;
}

float ListTableWidget::getSumOfColumn(int colIndex, int upto)
{
    float sum = 0;
    int end = (upto < rowCount())? upto: rowCount();
    for(int i=0; i < end; i++)
    {
        sum += getItem(i, colIndex).toFloat();
    }
    return sum;
}

QString ListTableWidget::getHeader(int index)
{
    return header.at(index);
}

QString ListTableWidget::toCommaSeperated()
{
    QString csv = "";
    for(int i = 0; i < columnCount(); i++)
    {
        csv += horizontalHeaderItem(i)->text();
        if(i != columnCount() - 1)
            csv += ",";
    }
    for(int i = 0; i < rowCount(); i++)
    {
        csv += "\r\n";
        for(int j = 0; j < columnCount(); j++)
        {
            csv += getItem(i, j);
            if(j != columnCount() - 1)
                csv += ",";
        }
    }
    return csv;
}
