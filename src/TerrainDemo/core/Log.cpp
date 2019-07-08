/**
 * @Brief       Logging mechanism body
 * @Author      Petr Fusek
 * @Project     GPUTerrainDemo
 * @File        Logger.h
 */

#include <TerrainDemo/Interfaces/ILogger.h>
#include <TerrainDemo/core/Log.h>
#include <assert.h>

using namespace std;
using namespace TerrainDemo::core;
using namespace TerrainDemo::Interfaces;

shared_ptr<ILogger> Log::_logger;

void Log::setLogger(shared_ptr<ILogger> logger = nullptr)
{
    if (logger != nullptr)
        _logger = logger;
    else
        _logger = make_shared<BasicLogger>();
}

std::shared_ptr<ILogger>& Log::getLogger()
{
    if (_logger == nullptr)
        setLogger();
    return _logger;
}