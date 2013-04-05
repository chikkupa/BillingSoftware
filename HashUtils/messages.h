#ifndef MESSAGES_H
#define MESSAGES_H

#include <QtCore>

class Messages
{
public:
    Messages();

    static void showMessage(QString message);
    static void showCriticalMessage(QString message);
    static bool confirmMessage(QString message, QString title);
};

#endif // MESSAGES_H
