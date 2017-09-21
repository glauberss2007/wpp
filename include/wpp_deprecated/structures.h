#pragma once

#include <unordered_map>
#include "json.hpp"
#include "bustache/model.hpp"

namespace wpp
{
    using ci_map = std::unordered_multimap<std::string, std::string>;
    using json = nlohmann::json;
    namespace mustache = bustache;
}
