#include <Logger.hpp>
#include <iostream>
#include <fstream>

namespace RType
{
    void Logger::Log(const std::string& msg)
    {
        std::cerr << msg << std::endl;
    }

    void Logger::Log(const std::string& filename, const std::string& msg)
    {
        std::ofstream file;

        file.open(filename);
        file << msg << std::endl;
        file.close();
    }
}