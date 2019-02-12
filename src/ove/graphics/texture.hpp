#pragma once

#include <ove/core/util/types.hpp>

namespace graphics {

enum wrap_mode {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER
};

enum frag_filter {
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR
};

enum pixel_channel {
    RGB,
    RGBA
};

struct texture_t : public resource_t {
    texture_t()
        : m_sWrapMode(wrap_mode::REPEAT)
        , m_tWrapMode(wrap_mode::REPEAT)
        , m_minFilter(frag_filter::LINEAR)
        , m_magFilter(frag_filter::LINEAR)
        , m_width(0)
        , m_height(0)
        , m_bpp(0)
        , m_data(nullptr)
    {
    }

    virtual void bind(u8 idx) const = 0;

    virtual void unbind() const = 0;

    virtual void submit(u32 width, u32 height, u32 bpp, bool mm, u8* data) = 0;

    virtual void load(const std::string& filename) = 0;

    virtual void dispose() = 0;

    inline void setWrapMode(wrap_mode s, wrap_mode t)
    {
        m_sWrapMode = s;
        m_tWrapMode = t;
        setWrapMode();
    }

    inline void setFilter(frag_filter min, frag_filter mag)
    {
        m_minFilter = min;
        m_magFilter = mag;
        setFilter();
    }

    inline wrap_mode getSWrapMode() const { return m_sWrapMode; }

    inline wrap_mode getTWrapMode() const { return m_tWrapMode; }

    inline wrap_mode getRWrapMode() const { return m_rWrapMode; }

    inline frag_filter getMinFilter() const { return m_minFilter; }

    inline frag_filter getMagFilter() const { return m_magFilter; }

    inline u32 getWidth() const { return m_width; }

    inline u32 getHeight() const { return m_height; }

    inline u32 getBPP() const { return m_bpp; }

    inline u8* getData() const { return m_data; }

protected:
    virtual void setWrapMode() = 0;

    virtual void setFilter() = 0;

    wrap_mode m_sWrapMode;
    wrap_mode m_tWrapMode;
    wrap_mode m_rWrapMode;
    frag_filter m_minFilter;
    frag_filter m_magFilter;
    u32 m_width;
    u32 m_height;
    u32 m_bpp;
    u8* m_data;
};

struct cubemap_t : public texture_t {
    cubemap_t() {}

    virtual void bind(u8 idx) const = 0;

    virtual void unbind() const = 0;

    virtual void submit(u32 width, u32 height, u32 bpp, bool mm, u8* data) = 0;

    virtual void load(const std::string& filename) = 0;

    virtual void dispose() = 0;

    inline void setWrapMode(wrap_mode s, wrap_mode t, wrap_mode r)
    {
        m_sWrapMode = s;
        m_tWrapMode = t;
        m_rWrapMode = r;
        setWrapMode();
    }

    inline wrap_mode getRWrapMode() const { return m_rWrapMode; }

protected:
    virtual void setWrapMode() = 0;

    virtual void setFilter() = 0;

    wrap_mode m_rWrapMode;
};

}
