#include "window.hpp"

namespace ove {
namespace system {

    void window_t::setCloseCallback(window_close_fn callback)
    {
        m_close_fn = callback;
    }

    void window_t::setSizeCallback(window_size_fn callback)
    {
        m_size_fn = callback;
    }

    void window_t::setPositionCallback(window_pos_fn callback)
    {
        m_pos_fn = callback;
    }

    void window_t::setMouseButtonCallback(window_mouse_btn_fn callback)
    {
        m_mouse_btn_fn = callback;
    }

    void window_t::setCursorPosCallback(window_cursor_pos_fn callback)
    {
        m_cursor_pos_fn = callback;
    }

    void window_t::setCursorEnterCallback(window_cursor_enter_fn callback)
    {
        m_cursor_enter_fn = callback;
    }

    void window_t::setScrollCallback(window_scroll_fn callback)
    {
        m_scroll_fn = callback;
    }

    void window_t::setKeyCallback(window_key_fn callback)
    {
        m_key_fn = callback;
    }

    void window_t::setCharCallback(window_char_fn callback)
    {
        m_char_fn = callback;
    }

}
}
