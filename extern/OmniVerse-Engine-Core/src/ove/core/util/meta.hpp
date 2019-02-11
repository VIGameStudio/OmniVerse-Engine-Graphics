#pragma once

/**
 * TODO:
 * Revise
 */

#include <ove/core/util/types.hpp>

namespace core {
namespace meta {

    template <typename T>
    struct id {
        using type = T;
    };

    template <typename T>
    using type_of = typename T::type;

    template <size_t... N>
    struct sizes : id<sizes<N...>> {
    };

}
}
