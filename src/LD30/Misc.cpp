#include <LD30/Misc.hpp>
#include <fstream>
#include <streambuf>
#include <direct.h>

std::string ld::Misc::readTextFile(const std::string& path, const bool create)
{
    std::ifstream stream(path);
    std::string str("");

    if (stream.good() && !stream.eof())
    {
        str = std::string(std::istreambuf_iterator<char>(stream),
                           std::istreambuf_iterator<char>());
    }
    else if (create && str.empty())
    {
        std::ofstream output(path);
        output << "{}\0";
        output.close();
        str = "{}";
    }

    return str;
}

std::string ld::Misc::getHomeDir(const std::string& folder)
{
    std::string path(std::getenv("USERPROFILE"));
    path += "\\Documents\\my games";
    _mkdir(path.c_str());
    path += "\\" + folder;
    _mkdir(path.c_str());
    path += "\\";

    return path;
}

float ld::Misc::getRandomFloat(const float min, const float max)
{
    return (min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min))));
}

int ld::Misc::getRandomInt(const int min, const int max)
{
    return (min + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (max - min))));
}
