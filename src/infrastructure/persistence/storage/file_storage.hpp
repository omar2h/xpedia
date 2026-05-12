#pragma once

#include "../../../third_party/json.hpp"

using json = nlohmann::json;

class FileStorage
{
public:
    [[nodiscard]] json readAll(const std::string &path) const;

    void writeJsonToFile(const std::string &path, const json &obj, bool append) const;

    [[nodiscard]] std::vector<std::string> readJsonAttributeFromFile(const std::string &path,
                                                       const std::string &attribute) const;

    [[nodiscard]] json getObjectWithId(const std::string &path, const std::string &id) const;

    void deleteObjectWithId(const std::string &path, const std::string &id) const;

    [[nodiscard]] json getObjectsWithAttribute(const std::string &path, const std::string &attribute,
                                 const std::string &value) const;
};