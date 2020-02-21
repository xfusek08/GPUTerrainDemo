
#pragma once

#include <string>

namespace gpd
{
    namespace interfaces
    {
        /**
         * @brief Logger interface
         */
        class LoggerInterface
        {
        public:
            virtual void writeError(std::string message) const = 0;
            virtual void writeWarning(std::string message) const = 0;
            virtual void writeInfo(std::string message) const = 0;
            virtual void writeDebug(std::string message) const = 0;
        };
    }
}
