#include "x11_window.hpp"

namespace ove {
namespace system {

    bool x11_window_t::create(const char* title, unsigned int width, unsigned int height)
    {
        GLint attribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

        m_pDisplay = XOpenDisplay(NULL);

        if (m_pDisplay == nullptr) {
            // Cannot connect to X server
            return false;
        }

        m_root = DefaultRootWindow(m_pDisplay);

        m_pVisualInfo = glXChooseVisual(m_pDisplay, 0, attribs);

        if (m_pVisualInfo == nullptr) {
            // No appropriate visual found
            return false;
        }

        Colormap colorMap = XCreateColormap(m_pDisplay, m_root, m_pVisualInfo->visual, AllocNone);

        XSetWindowAttributes swa;
        swa.colormap = colorMap;
        swa.event_mask = ExposureMask | KeyPressMask;

        m_window = XCreateWindow(m_pDisplay, m_root, 0, 0, width, height, 0, m_pVisualInfo->depth, InputOutput, m_pVisualInfo->visual, CWColormap | CWEventMask, &swa);

        XSelectInput(m_pDisplay, m_window,
            ExposureMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | KeyPressMask | KeyReleaseMask | FocusChangeMask);

        XMapWindow(m_pDisplay, m_window);

        XStoreName(m_pDisplay, m_window, title);
        m_title = title;

        m_context = glXCreateContext(m_pDisplay, m_pVisualInfo, NULL, GL_TRUE);
        glXMakeCurrent(m_pDisplay, m_window, m_context);

        m_wmDeleteMessage = XInternAtom(m_pDisplay, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_pDisplay, m_window, &m_wmDeleteMessage, 1);

        m_shouldClose = false;

        return true;
    }

    void x11_window_t::close()
    {
        glXMakeCurrent(m_pDisplay, None, NULL);
        glXDestroyContext(m_pDisplay, m_context);
        XDestroyWindow(m_pDisplay, m_window);
        XCloseDisplay(m_pDisplay);
    }

    void x11_window_t::pollEvents()
    {
        while (!m_shouldClose && XPending(m_pDisplay)) {
            XNextEvent(m_pDisplay, &m_event);

            switch (m_event.type) {
            case Expose:
                XGetWindowAttributes(m_pDisplay, m_window, &m_attribs);
                break;

            case ButtonPress:
                switch (m_event.xbutton.button) {
                case Button1:
                    if (m_mouse_btn_fn) {
                        m_mouse_btn_fn(this, BUTTON_1, BUTTON_PRESSED, 0);
                    }
                    break;
                case Button2:
                    if (m_mouse_btn_fn) {
                        m_mouse_btn_fn(this, BUTTON_2, BUTTON_PRESSED, 0);
                    }
                    break;
                case Button3:
                    if (m_mouse_btn_fn) {
                        m_mouse_btn_fn(this, BUTTON_3, BUTTON_PRESSED, 0);
                    }
                    break;
                case Button4:
                    if (m_scroll_fn) {
                        m_scroll_fn(this, 0, 100);
                    }
                    break;
                case Button5:
                    if (m_scroll_fn) {
                        m_scroll_fn(this, 0, -100);
                    }
                    break;
                }
                break;

            case ButtonRelease:
                switch (m_event.xbutton.button) {
                case Button1:
                    if (m_mouse_btn_fn) {
                        m_mouse_btn_fn(this, BUTTON_1, BUTTON_RELEASED, 0);
                    }
                    break;
                case Button2:
                    if (m_mouse_btn_fn) {
                        m_mouse_btn_fn(this, BUTTON_2, BUTTON_RELEASED, 0);
                    }
                    break;
                case Button3:
                    if (m_mouse_btn_fn) {
                        m_mouse_btn_fn(this, BUTTON_3, BUTTON_RELEASED, 0);
                    }
                    break;
                case Button4:
                    if (m_scroll_fn) {
                        m_scroll_fn(this, 0, 100);
                    }
                    break;
                case Button5:
                    if (m_scroll_fn) {
                        m_scroll_fn(this, 0, -100);
                    }
                    break;
                }
                break;

            case MotionNotify:
                if (m_cursor_pos_fn) {
                    m_cursor_pos_fn(this, m_event.xmotion.x, m_event.xmotion.y);
                }
                break;

            case EnterNotify:
                if (m_cursor_enter_fn) {
                    m_cursor_enter_fn(this, true);
                }
                break;

            case LeaveNotify:
                if (m_cursor_enter_fn) {
                    m_cursor_enter_fn(this, false);
                }
                break;

            case FocusIn:
                if (m_focus_fn) {
                    m_focus_fn(this, true);
                }
                break;

            case FocusOut:
                if (m_focus_fn) {
                    m_focus_fn(this, false);
                }
                break;

            case KeyPress:
                if (m_key_fn) {
                    m_key_fn(this, m_event.xkey.keycode, 0, KEY_PRESSED, 0);
                }
                break;

            case KeyRelease:
                if (m_key_fn) {
                    m_key_fn(this, m_event.xkey.keycode, 0, KEY_RELEASED, 0);
                }
                break;

            case ClientMessage:
                if (m_event.xclient.data.l[0] == (long int)m_wmDeleteMessage) {
                    if (m_close_fn) {
                        m_close_fn(this);
                    }
                    m_shouldClose = true;
                    close();
                }
                break;
            }
        }
    }

    void x11_window_t::swapBuffers()
    {
        glXSwapBuffers(m_pDisplay, m_window);
    }

    bool x11_window_t::shouldClose()
    {
        return m_shouldClose;
    }

    void x11_window_t::setTitle(const char* title)
    {
        XStoreName(m_pDisplay, m_window, title);
        m_title = title;
    }

    void x11_window_t::setSize(unsigned int width, unsigned int height)
    {
        XMoveResizeWindow(m_pDisplay, m_window, 0, 0, width, height);
    }

    const char* x11_window_t::getTitle()
    {
        return m_title;
    }

    void x11_window_t::getSize(unsigned int& width, unsigned int& height)
    {
        width = m_attribs.width;
        height = m_attribs.height;
    }
}
}
