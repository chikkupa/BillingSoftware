#ifndef LISTTABLEWIDGET_H
#define LISTTABLEWIDGET_H

#include <QTableWidget>

class ListTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit ListTableWidget(QWidget *parent = 0);
    void setList(QStringList list, bool editable = false);
    void set2DList(QList<QStringList> list, bool editable = false);
    QStringList getList();
    QString getItem(int, int);
    void setEditable(bool);
    void setEditableColumn(int row, bool editable);
    void addEndRow(QString);
    float getSumOfColumn(int);
    float getSumOfColumn(int, int);
    QString getHeader(int);
    QString toCommaSeperated();

    private:
        QStringList header;
};

#endif // LISTTABLEWIDGET_H
