#pragma once

/**
 * TODO:
 * Revise
 */

#include <ove/core/util/types.hpp>

namespace core {

struct btype_t {
    virtual size_t id() const = 0;

protected:
    static size_t reg_id()
    {
        static size_t s_counter = 0;
        return s_counter++;
    }
};

template <typename T>
struct type_t : btype_t {
    virtual size_t id() const { return gid(); }

    static size_t gid()
    {
        static size_t s_id = reg_id();
        return s_id;
    }
};

}
