#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"

using namespace genv;

class Jatekmester;

class Widget {
protected:
    Jatekmester* _jatekmester;
    int _x, _y, _size_x, _size_y;
public:
    Widget(Jatekmester* jatekmester,int x, int y, int sx, int sy);
    Widget(Jatekmester* jatekmester,int x, int y, int sy);
    Widget(Jatekmester* jatekmester,int x, int y);
    virtual bool selected(int mouse_x, int mouse_y);
    virtual void draw() = 0;
    virtual void handle(const event &ev) = 0;
};

#endif // WIDGETS_HPP_INCLUDED
