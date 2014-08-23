#include <LD30/Settings.hpp>
#include <LD30/Misc.hpp>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <fstream>


namespace rj = rapidjson;

namespace
{
    rj::Document ns_doc;
    std::string ns_file;

    rj::Value* getValue(const std::string& name)
    {
        if (ns_doc.HasMember(name.c_str()))
            return &ns_doc[name.c_str()];

        return nullptr;
    }
}

bool ld::Settings::init(const std::string& path)
{
    ns_file = path;
    std::string string = Misc::readTextFile(path, true);

    if (!string.empty())
    {
        ns_doc.Parse<0>(string.c_str());

        if (ns_doc.HasParseError())
            return false;
    }

    return true;
}

bool ld::Settings::getBool(const std::string& name, const bool defaultValue)
{
    auto value = getValue(name);

    if (value && value->IsBool())
        return value->GetBool();
    else
    {
        ns_doc.AddMember(name.c_str(), defaultValue, ns_doc.GetAllocator());
    }

    return defaultValue;
}

int ld::Settings::getInt(const std::string& name, const int defaultValue)
{
    auto value = getValue(name);

    if (value && value->IsInt())
        return value->GetInt();
    else
    {
        ns_doc.AddMember(name.c_str(), defaultValue, ns_doc.GetAllocator());
    }

    return defaultValue;
}

float ld::Settings::getFloat(const std::string& name, const float defaultValue)
{
    auto value = getValue(name);

    if (value && value->IsDouble())
        return static_cast<float>(value->GetDouble());
    else
    {
        ns_doc.AddMember(name.c_str(), static_cast<const double>(defaultValue), ns_doc.GetAllocator());
    }

    return defaultValue;
}

std::string ld::Settings::getString(const std::string& name, const std::string& defaultValue)
{
    auto value = getValue(name);

    if (value && value->IsString())
        return std::string(value->GetString());
    else
    {
        ns_doc.AddMember(name.c_str(), defaultValue.c_str(), ns_doc.GetAllocator());
    }
    
    return defaultValue;
}

bool ld::Settings::writeSettings()
{
    if (ns_file.empty())
        return false;

    rj::StringBuffer buffer;
    rj::PrettyWriter<rj::StringBuffer> writer(buffer);
    ns_doc.Accept(writer);
    
    std::ofstream stream(ns_file.c_str());

    if (!stream)
        return false;

    stream << buffer.GetString();

    stream.close();

    return true;
}
