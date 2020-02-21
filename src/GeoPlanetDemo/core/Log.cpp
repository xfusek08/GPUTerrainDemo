/**
 * @Brief       Logging mechanism body
 * @Author      Petr Fusek
 * @Project     TerrainLibDemo
 * @File        Logger.h
 */

#include <GeoPlanetDemo/interfaces/LoggerInterface.h>
#include <GeoPlanetDemo/core/Log.h>
#include <assert.h>

using namespace std;
using namespace gpd::core;
using namespace gpd::interfaces;

shared_ptr<LoggerInterface> Log::logger;

void Log::setLogger(shared_ptr<LoggerInterface> logger = nullptr)
{
    if (logger != nullptr)
        Log::logger = logger;
    else
        Log::logger = make_shared<BasicLogger>();
}

std::shared_ptr<LoggerInterface>& Log::getLogger()
{
    if (Log::logger == nullptr)
        setLogger();
    return Log::logger;
}