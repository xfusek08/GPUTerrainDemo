/**
 * @Brief       Logging mechanism header
 * @Description Static Log class keeping providing single instance of ILogger interface
 *              ILogger interface is implemented by BasicLogger class and passed as default
 *              argument for log initiation.
 *              Also a wrapping macros for logging are defined.
 * @Author      Petr Fusek
 * @Project     GPUTerrainDemo
 * @File        Logger.h
 */

#pragma once

#include <memory>
#include <TerrainDemo/Interfaces/ILogger.h>

namespace TerrainDemo
{
    class Log
    {
    public:
        static void setLogger(std::shared_ptr<TerrainDemo::Interfaces::ILogger> logger);

        static std::shared_ptr<TerrainDemo::Interfaces::ILogger> &getLogger();

    private:
        static std::shared_ptr<TerrainDemo::Interfaces::ILogger> _logger;
    };
} // namespace TerrainDemo

#define GPTR_LOG_ERROR(...) TerrainDemo::Log::getLogger()->writeError(__VA_ARGS__)
#define GPTR_LOG_WARNING(...) TerrainDemo::Log::getLogger()->writeWarning(__VA_ARGS__)
#define GPTR_LOG_INFO(...) TerrainDemo::Log::getLogger()->writeInfo(__VA_ARGS__)

#ifdef GT_DEBUG
#define GPTR_LOG_Debug(...) TerrainDemo::Log::getLogger()->writeDebug(__VA_ARGS__)
#else
#define GPTR_LOG_Debug(...)
#endif
