#include "textdisplay.hpp"
#include <iostream>
#include <functional>
#include <sstream>

using namespace genv;

Textdisplay::Textdisplay(Jatekmester* jatekmester, std::string display, int x, int y, bool rendezes, int fontsize) : Widget(jatekmester, x, y), _felirat(display), _rendezes(rendezes), _fontsize(fontsize) {
    gout.load_font("Retro Gaming.ttf", _fontsize);
    _size_x = gout.twidth(_felirat);
    _size_y = gout.cascent() + gout.cdescent();
}

void Textdisplay::talaltlott(int value1, int value2){
    std::stringstream ss;
    _value1 = value1;
    _value2 = value2;
    ss<<value1<<'/'<<value2;
    _felirat = ss.str();
}

void Textdisplay::sullyedt(int value1){
    std::stringstream ss;
    _value1 = value1;
    ss<<_value1<<" sullyedt";
    _felirat = ss.str();
}

void Textdisplay::handle(const event &ev) {}

void Textdisplay::draw() {
    gout.load_font("Retro Gaming.ttf", _fontsize);
    if (_rendezes) {
        gout << move_to(_x+XX/2-_size_x/2, _y)<<color(255,255,255)<<text(_felirat);
    } else {
        gout << move_to(_x, _y) <<move_to(_x+(_size_x-gout.twidth(_felirat))/2, _y+(_size_y-(gout.cascent()+gout.cdescent()))/2)<<color(255,255,255)<<text(_felirat);
    }
}
