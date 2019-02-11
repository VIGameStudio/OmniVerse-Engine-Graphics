#include <ove/system/x11/x11_window.hpp>

#include <iostream>
#include <GL/glu.h>
#include <iostream>

using namespace ove::system;

void cursor_pos_fn(window_t*win, double x, double y)
{
    printf("x:%.0f, y:%.0f\n", x, y);
}

void key_fn(window_t*win, int key, int scanCode, int action, int mods)
{
    std::cout << "k:" << key << std::endl;
}

int main()
{
    window_t* window = new ove::system::x11_window_t();

    if (!window->create("Demo", 640, 480))
    {
        return EXIT_FAILURE;
    }

    window->setCursorPosCallback(cursor_pos_fn);
    window->setKeyCallback(key_fn);

    while(!window->shouldClose())
    {
        unsigned int width, height;
        window->getSize(width, height);

        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, width, height);
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.f, 1.f, -1.f, 1.f, 1.f, 20.f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.f, 0.f, 10.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

        glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-.75f, -.75f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(.75f, -.75f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(.75f, .75f, 0.f);
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-.75f, .75f, 0.f);
        glEnd();

        window->swapBuffers();
        window->pollEvents();

        //printf("update\n");
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}
