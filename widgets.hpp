#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"

using namespace genv;

class Window;

class Widget {
protected:
    Window* _w;
    int _x, _y, _size_x, _size_y;
public:
    Widget(Window* window,int x, int y, int sx, int sy);
    Widget(Window* window,int x, int y, int sy);
    Widget(Window* window,int x, int y);
    virtual bool selected(int mouse_x, int mouse_y);
    virtual void output() = 0;
    virtual void draw() = 0;
    virtual void handle(const event &ev) = 0;
};

#endif // WIDGETS_HPP_INCLUDED
