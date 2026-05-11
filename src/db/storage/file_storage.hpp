#pragma once

#include "../../third_party/json.hpp"

using json = nlohmann::json;

class FileStorage
{
public:
    void writeJsonToFile(const std::string &path, const json &obj, bool append) const;

    std::vector<std::string> readJsonAttributeFromFile(const std::string &path,
                                                       const std::string &attribute) const;

    json getObjectWithId(const std::string &path, const std::string &id) const;

    void deleteObjectWithId(const std::string &path, const std::string &id) const;

    json getObjectsWithAttribute(const std::string &path, const std::string &attribute,
                                 const std::string &value) const;
};