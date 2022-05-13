#include "button.hpp"
#include <iostream>
#include <functional>
#include <sstream>

using namespace genv;

Button::Button(Jatekmester* jatekmester, std::string display, int x, int y, int sx, int sy, std::function<void()> asd) : Widget(jatekmester, x, y, sx, sy), _felirat(display), _f(asd) {}

void Button::handle(const event &ev) {
    if (selected(ev.pos_x, ev.pos_y) && ev.button == btn_left) {
        _nyomott=true;
        _f();
    }
    if (ev.button == -btn_left) _nyomott = false;
}
void Button::draw() {
    gout.load_font("LiberationSans-Regular.ttf", 20);
    if (_nyomott) gout<<color(255,100,200); else gout<<color(200, 200, 200);
    gout << move_to(_x, _y) << box(_size_x, _size_y)<<move_to(_x+(_size_x-gout.twidth(_felirat))/2, _y+(_size_y-(gout.cascent()+gout.cdescent()))/2)<<color(0,0,0)<<text(_felirat);
}
