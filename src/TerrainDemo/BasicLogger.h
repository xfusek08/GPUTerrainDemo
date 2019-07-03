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

#include <iostream>

#include <TerrainDemo/Interfaces/ILogger.h>

namespace TerrainDemo
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

} // namespace TerrainDemo
