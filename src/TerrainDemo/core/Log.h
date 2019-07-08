#pragma once

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


#include <iostream>
#include <memory>
#include <TerrainDemo/Interfaces/ILogger.h>
#include <TerrainDemo/core/Utils.h>

namespace TerrainDemo
{
    namespace core
    {
        /**
         * @brief Basic default logger for writing on standard error output
         */
        class BasicLogger : public TerrainDemo::Interfaces::ILogger
        {
        public:
            inline void writeError(std::string message) const override { std::cerr << "Error: " << message << std::endl; }
            inline void writeWarning(std::string message) const override { std::cerr << "Warning: " << message << std::endl; }
            inline void writeInfo(std::string message) const override { std::cerr << "Info: " << message << std::endl; }
            inline void writeDebug(std::string message) const override { std::cerr << "Debug: " << message << std::endl; }
        };

        /**
         * @brief static class providing logger instance
         */
        class Log
        {
        public:
            static void setLogger(std::shared_ptr<TerrainDemo::Interfaces::ILogger> logger);

            static std::shared_ptr<TerrainDemo::Interfaces::ILogger> &getLogger();

        private:
            static std::shared_ptr<TerrainDemo::Interfaces::ILogger> _logger;
        };
    } // namespace core
} // namespace TerrainDemo

#define GPTR_LOG_ERROR(...) TerrainDemo::core::Log::getLogger()->writeError(STREAM_TO_STR(__VA_ARGS__))
#define GPTR_LOG_WARNING(...) TerrainDemo::core::Log::getLogger()->writeWarning(STREAM_TO_STR(__VA_ARGS__))
#define GPTR_LOG_INFO(...) TerrainDemo::core::Log::getLogger()->writeInfo(STREAM_TO_STR(__VA_ARGS__))

#ifdef GT_DEBUG
#define GPTR_LOG_Debug(...) TerrainDemo::core::Log::getLogger()->writeDebug(STREAM_TO_STR(__VA_ARGS__))
#else
#define GPTR_LOG_Debug(...)
#endif
