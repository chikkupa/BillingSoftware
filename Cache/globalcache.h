#ifndef GLOBALCACHE_H
#define GLOBALCACHE_H

#include <QtCore>

class GlobalCache
{
public:
    GlobalCache();

private:
    static int screenWidth;
    static int screenHeight;
    static QString version;
    static QString buildDate;

public:
    static void setScreenWidth(int width);
    static void setScreenHeight(int height);
    static int getScreenWidth();
    static int getScreenHeight();
    static QString getVersion();
    static QString getBuildDate();
};

#endif // GLOBALCACHE_H
