#pragma once

#include "../../third_party/json.hpp"

using json = nlohmann::json;

class FileStorage
{
public:
    void write_json_to_file(const std::string &path, const json &obj, bool append) const;

    std::vector<std::string> read_json_attribute_from_file(const std::string &path,
                                                           const std::string &attribute) const;

    json get_object_with_id(const std::string &path, const std::string &id) const;

    void delete_object_with_id(const std::string &path, const std::string &id) const;

    json getObjectsWithAttribute(const std::string &path, const std::string &attribute,
                                 const std::string &value) const;
};