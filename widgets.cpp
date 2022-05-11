#include "widgets.hpp"
#include "graphics.hpp"
#include "window.hpp"
#include <iostream>
using namespace genv;

Widget::Widget(Window* window, int x, int y, int sx, int sy) : _w(window),_x(x), _y(y), _size_x(sx), _size_y(sy) {}

Widget::Widget(Window* window, int x, int y, int sy) : _w(window),_x(x), _y(y), _size_y(sy) {}

Widget::Widget(Window* window, int x, int y) : _w(window),_x(x), _y(y) {}

bool Widget::selected(int mouse_x, int mouse_y) {
    return mouse_x > _x && mouse_x < _x + _size_x && mouse_y > _y && mouse_y < _y + _size_y;
}
