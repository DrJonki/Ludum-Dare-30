#pragma once

#include <string>


namespace ld
{
    static const float pi = 3.141592653f;

    class Misc
    {
    public:

        static std::string readTextFile(const std::string& path, const bool create);

        static std::string getHomeDir(const std::string& folder);
    };
}