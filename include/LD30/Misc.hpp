#include <string>


namespace ld
{
    class Misc
    {
    public:

        static std::string readTextFile(const std::string& path, const bool create);

        static std::string getHomeDir(const std::string& folder);
    };
}