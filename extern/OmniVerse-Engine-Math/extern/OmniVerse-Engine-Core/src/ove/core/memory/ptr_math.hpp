#pragma once

#include <ove/core/util/assert.hpp>
#include <ove/core/util/types.hpp>

namespace core {
namespace pmath {

    ptrdiff alignForward(uptr address, u8 alignment);

    const void* alignForward(const void* address, u8 alignment);

    void* alignBackward(void* address, u8 alignment);

    const void* alignBackward(const void* address, u8 alignment);

    u8 alignForwardAdjustment(const void* address, u8 alignment);

    u8 alignForwardAdjustmentWithHeader(const void* address, u8 alignment, u8 headerSize);

    u8 alignBackwardAdjustment(const void* address, u8 alignment);

    void* add(void* p, u64 x);

    const void* add(const void* p, u64 x);

    void* subtract(void* p, u64 x);

    const void* subtract(const void* p, u64 x);

    inline ptrdiff alignForward(uptr address, u8 alignment)
    {
        ASSERT(alignment >= 1);
        ASSERT(alignment <= 128);
        ASSERT((alignment & (alignment - 1)) == 0); // Must be pwr of 2!

        // u8 mask = (alignment-1);
        // uptr misalignment = (address & mask);
        ptrdiff adjustment = alignment - (address & (alignment - 1));
        ASSERT(adjustment < 256);
        return adjustment;
    }

    inline const void* alignForward(const void* address, u8 alignment)
    {
        return (void*)((reinterpret_cast<uptr>(address) + static_cast<uptr>(alignment - 1)) & static_cast<uptr>(~(alignment - 1)));
    }

    inline void* alignBackward(void* address, u8 alignment)
    {
        return (void*)(reinterpret_cast<uptr>(address) & static_cast<uptr>(~(alignment - 1)));
    }

    inline const void* alignBackward(const void* address, u8 alignment)
    {
        return (void*)(reinterpret_cast<uptr>(address) & static_cast<uptr>(~(alignment - 1)));
    }

    inline u8 alignForwardAdjustment(const void* address, u8 alignment)
    {
        u8 adjustment = alignment - (reinterpret_cast<uptr>(address) & static_cast<uptr>(alignment - 1));

        if (adjustment == alignment)
            return 0; // already aligned

        return adjustment;
    }

    inline u8 alignForwardAdjustmentWithHeader(const void* address, u8 alignment,
        u8 headerSize)
    {
        u8 adjustment = alignForwardAdjustment(address, alignment);

        u8 neededSpace = headerSize;

        if (adjustment < neededSpace) {
            neededSpace -= adjustment;

            // Increase adjustment to fit header
            adjustment += alignment * (neededSpace / alignment);

            if (neededSpace % alignment > 0)
                adjustment += alignment;
        }

        return adjustment;
    }

    inline u8 alignBackwardAdjustment(const void* address, u8 alignment)
    {
        u8 adjustment = reinterpret_cast<uptr>(address) & static_cast<uptr>(alignment - 1);

        if (adjustment == alignment)
            return 0; // already aligned

        return adjustment;
    }

    inline void* add(void* p, u64 x)
    {
        return (void*)(reinterpret_cast<uptr>(p) + x);
    }

    inline const void* add(const void* p, u64 x)
    {
        return (const void*)(reinterpret_cast<uptr>(p) + x);
    }

    inline void* subtract(void* p, u64 x)
    {
        return (void*)(reinterpret_cast<uptr>(p) - x);
    }

    inline const void* subtract(const void* p, u64 x)
    {
        return (const void*)(reinterpret_cast<uptr>(p) - x);
    }

}
}
