#pragma once

#include "json.hpp"
#include <string>

namespace json_utils
{
template <typename T> T safeValue(const nlohmann::json& j, const std::string& key, const T& fallback = T{})
{
    return j.contains(key) && !j.at(key).is_null() ? j.at(key).get<T>() : fallback;
}
} // namespace json_utils