#include "file_storage.hpp"

#include <fstream>

void FileStorage::writeJsonToFile(const std::string &path, const json &obj, bool append) const
{
    std::fstream file_handler(path.c_str());

    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file");
    }

    json arr;

    file_handler.seekg(0, std::ios::beg);

    if (file_handler.peek() != std::ifstream::traits_type::eof())
    {
        file_handler >> arr;
    }

    file_handler.close();

    if (!append)
    {
        arr.clear();
    }

    arr.push_back(obj);

    std::ofstream out(path.c_str());

    out << arr.dump(4);
}

std::vector<std::string> FileStorage::readJsonAttributeFromFile(const std::string &path,
                                                                const std::string &attribute) const
{
    std::fstream file_handler(path.c_str());

    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file");
    }

    json arr;

    file_handler >> arr;

    std::vector<std::string> attributes;

    for (const auto &obj : arr)
    {
        attributes.push_back(
            obj.value(attribute, ""));
    }

    return attributes;
}

json FileStorage::getObjectWithId(const std::string &path, const std::string &id) const
{
    std::fstream file_handler(path.c_str());

    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file");
    }

    json arr;

    file_handler >> arr;

    for (const auto &obj : arr)
    {
        if (obj.value("id", "") == id)
        {
            return obj;
        }
    }

    return json{};
}

void FileStorage::deleteObjectWithId(const std::string &path, const std::string &id) const
{
    std::fstream file_handler(path.c_str());

    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file");
    }

    json arr;

    file_handler >> arr;

    file_handler.close();

    json updated = json::array();

    for (const auto &obj : arr)
    {
        if (obj.value("id", "") != id)
        {
            updated.push_back(obj);
        }
    }

    std::ofstream out(path.c_str());

    out << updated.dump(4);
}

json FileStorage::getObjectsWithAttribute(const std::string &path, const std::string &attribute,
                                          const std::string &value) const
{
    std::fstream file_handler(path.c_str());

    if (file_handler.fail())
    {
        throw std::runtime_error("Failed to open file");
    }

    json arr;

    file_handler >> arr;

    json result = json::array();

    for (const auto &obj : arr)
    {
        if (obj.value(attribute, "") == value)
        {
            result.push_back(obj);
        }
    }

    return result;
}