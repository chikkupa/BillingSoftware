#include "globalcache.h"
#include "databaseserver.h"

int GlobalCache::screenWidth = 0;
int GlobalCache::screenHeight = 0;
QString GlobalCache::version = "";
QString GlobalCache::buildDate = "";

GlobalCache::GlobalCache()
{
    screenWidth = 1024;
    screenHeight = 768;
}

void GlobalCache::setScreenWidth(int width)
{
    screenWidth = width;
}

void GlobalCache::setScreenHeight(int height)
{
    screenHeight = height;
}

int GlobalCache::getScreenWidth()
{
    return screenWidth;
}

int GlobalCache::getScreenHeight()
{
    return screenHeight;
}

QString GlobalCache::getVersion()
{
    DatabaseServer server;
    QString version = server.getSingleResult("select Value from Details where Field='Version'");
    return version;
}

QString GlobalCache::getBuildDate()
{
    DatabaseServer server;
    QString buildDate = server.getSingleResult("select Value from Details where Field='Build_Date'");
    return buildDate;
}
