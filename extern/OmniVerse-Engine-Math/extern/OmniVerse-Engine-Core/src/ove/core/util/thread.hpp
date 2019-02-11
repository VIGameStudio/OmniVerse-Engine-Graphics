#pragma once

/**
 * TODO:
 * Revise
 */

#include <thread>

#include <ove/core/util/time.hpp>

namespace core {
namespace thread {

    template <typename Res, typename Ratio>
    void sleep(ctime_t<Res, Ratio> duration)
    {
        std::this_thread::sleep_for(duration);
    }

}
}
