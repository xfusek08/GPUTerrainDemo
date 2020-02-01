#pragma once

/**
 * @Brief       Logging mechanism header
 * @Description Static Log class keeping providing single instance of LoggerInterface interface
 *              LoggerInterface interface is implemented by BasicLogger class and passed as default
 *              argument for log initiation.
 *              Also a wrapping macros for logging are defined.
 * @Author      Petr Fusek
 * @Project     TerrainLibDemo
 * @File        Logger.h
 */


#include <iostream>
#include <memory>

#include <GeoPlanetDemo/interfaces/LoggerInterface.h>

namespace  gpd
{
    namespace core
    {
        /**
         * @brief Basic default logger for writing on standard error output
         */
        class BasicLogger : public gpd::interfaces::LoggerInterface
        {
        public:
            inline void writeError(std::string message)   const override { std::cerr << "Error: " << message << std::endl; }
            inline void writeWarning(std::string message) const override { std::cerr << "Warning: " << message << std::endl; }
            inline void writeInfo(std::string message)    const override { std::cerr << "Info: " << message << std::endl; }
            inline void writeDebug(std::string message)   const override { std::cerr << "Debug: " << message << std::endl; }
        };

        /**
         * @brief static class providing logger instance
         */
        class Log
        {
        public:
            static void setLogger(std::shared_ptr<gpd::interfaces::LoggerInterface> logger);

            static std::shared_ptr<gpd::interfaces::LoggerInterface> &getLogger();

        private:
            static std::shared_ptr<gpd::interfaces::LoggerInterface> _logger;
        };
    } // namespace core
} // namespace  gpd
