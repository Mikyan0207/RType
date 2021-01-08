#include <iostream>
#include <RType.Common.hpp>

namespace RType
{
    class RTYPECOMMON_API Logger
    {
        public:
            static void Log(const std::string& msg);
            static void Log(const std::string& file, const std::string& msg);
    };
}