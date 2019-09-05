/**
 * @Brief       Logging mechanism body
 * @Author      Petr Fusek
 * @Project     TerrainLibDemo
 * @File        Logger.h
 */

#include <TerrainDemo/interfaces/LoggerInterface.h>
#include <TerrainDemo/core/Log.h>
#include <assert.h>

using namespace std;
using namespace TerrainDemo::core;
using namespace TerrainDemo::interfaces;

shared_ptr<LoggerInterface> Log::_logger;

void Log::setLogger(shared_ptr<LoggerInterface> logger = nullptr)
{
    if (logger != nullptr)
        _logger = logger;
    else
        _logger = make_shared<BasicLogger>();
}

std::shared_ptr<LoggerInterface>& Log::getLogger()
{
    if (_logger == nullptr)
        setLogger();
    return _logger;
}