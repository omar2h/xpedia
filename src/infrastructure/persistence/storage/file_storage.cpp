#include "file_storage.hpp"
#include "../../json_keys.hpp"
#include "../../../exception.hpp"

#include <cstdio>
#include <fstream>

void FileStorage::writeToFileAtomically(const std::string &path, const json &data) const
{
    std::string tmpPath = path + ".tmp";

    {
        std::ofstream out(tmpPath);
        if (out.fail())
            throw PersistenceException("Failed to write temp file");
        out << data.dump(4);
    }

    if (std::rename(tmpPath.c_str(), path.c_str()) != 0)
        throw PersistenceException("Failed to rename temp file");
}

json FileStorage::readAll(const std::string &path) const
{
    std::ifstream file_handler(path.c_str());

    if (file_handler.fail())
        return json::array();

    if (file_handler.peek() == std::ifstream::traits_type::eof())
        return json::array();

    json arr;
    file_handler >> arr;
    return arr;
}

void FileStorage::writeJsonToFile(const std::string &path, const json &obj, bool append) const
{
    json arr;

    {
        std::ifstream in(path);
        if (in)
            in >> arr;
    }

    if (!append)
        arr.clear();

    if (!arr.is_array())
        arr = json::array();

    arr.push_back(obj);

    writeToFileAtomically(path, arr);
}

std::vector<std::string> FileStorage::readJsonAttributeFromFile(const std::string &path,
                                                                const std::string &attribute) const
{
    std::ifstream file_handler(path.c_str());

    if (file_handler.fail() || file_handler.peek() == std::ifstream::traits_type::eof())
        return {};

    json arr;
    file_handler >> arr;

    std::vector<std::string> attributes;

    for (const auto &obj : arr)
        attributes.push_back(obj.value(attribute, ""));

    return attributes;
}

json FileStorage::getObjectWithId(const std::string &path, const std::string &id) const
{
    std::ifstream file_handler(path.c_str());

    if (file_handler.fail() || file_handler.peek() == std::ifstream::traits_type::eof())
        return json{};

    json arr;
    file_handler >> arr;

    for (const auto &obj : arr)
    {
        if (obj.value(JsonKeys::id, "") == id)
            return obj;
    }

    return json{};
}

void FileStorage::deleteObjectWithId(const std::string &path, const std::string &id) const
{
    json arr;

    {
        std::ifstream in(path);
        if (in)
            in >> arr;
    }

    if (!arr.is_array())
        return;

    json updated = json::array();

    for (const auto &obj : arr)
    {
        if (obj.value("id", "") != id)
            updated.push_back(obj);
    }

    writeToFileAtomically(path, updated);
}

json FileStorage::getObjectsWithAttribute(const std::string &path, const std::string &attribute,
                                          const std::string &value) const
{
    std::ifstream file_handler(path.c_str());

    if (file_handler.fail() || file_handler.peek() == std::ifstream::traits_type::eof())
        return json::array();

    json arr;
    file_handler >> arr;

    json result = json::array();

    for (const auto &obj : arr)
    {
        if (obj.value(attribute, "") == value)
            result.push_back(obj);
    }

    return result;
}