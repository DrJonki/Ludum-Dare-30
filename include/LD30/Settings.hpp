#include <string>

namespace ld
{
    class Settings
    {
    public:

        static bool init(const std::string& path);

        static bool getBool(const std::string& name, const bool defaultValue);

        static int getInt(const std::string& name, const int defaultValue);

        static float getFloat(const std::string& name, const float defaultValue);

        static std::string getString(const std::string& name, const std::string& defaultValue);

        static bool writeSettings();

    };
}