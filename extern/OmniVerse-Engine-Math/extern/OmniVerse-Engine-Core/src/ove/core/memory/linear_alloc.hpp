#pragma once

#include <ove/core/memory/alloc.hpp>

namespace core {

class linear_alloc_t : public alloc_t {
public:
    linear_alloc_t(u64 size);

    linear_alloc_t(u64 size, void* start);

    ~linear_alloc_t();

public:
    virtual void* allocate(u64 size, u8 alignment) override;

    virtual void deallocate(void* p) override;

    void clear();

private:
    void* m_pMarker;
};

}
