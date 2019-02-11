#pragma once

/**
 * TODO:
 * Revise
 */

#include <functional>

namespace core {
namespace hash {

    size_t encode(const std::string& str)
    {
        static std::hash<std::string> s_strhash;
        return s_strhash(str);
    }

}
}
