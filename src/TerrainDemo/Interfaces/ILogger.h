
#pragma once

#include <string>

namespace TerrainDemo
{
    namespace Interfaces
    {
        /**
         * @brief Logger interface
         */
        class ILogger
        {
        public:
            virtual void writeError(std::string message) const = 0;
            virtual void writeWarning(std::string message) const = 0;
            virtual void writeInfo(std::string message) const = 0;
            virtual void writeDebug(std::string message) const = 0;
        };
    }
}
