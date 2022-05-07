#include "mozgathatokep.hpp"

using namespace genv;

Mozgathatokep::Mozgathatokep(Window* window, int x, int y, int id, int bitmap[150][150]) : Widget(window, x, y), _id(id) {
    switch(_id) {
        case(0):
            _size_x = 150;
            _size_y = 30;
        break;
        case(1):
            _size_x = 120;
            _size_y = 30;
        break;
        case(2,3):
            _size_x = 90;
            _size_y = 30;
        break;
        case(4):
            _size_x = 60;
            _size_y = 30;
        break;
        default:
            _size_x = 30;
            _size_y = 30;
    }
    _talalt = {0};
    _fogotte = 1;
}

void Mozgathatokep::handle(const event &ev) {
    if (selected(ev.pos_x, ev.pos_y) && ev.button == btn_left) {
    }
}

void Mozgathatokep::draw() {
    for (int i=0; i<150; i++) {
        for (int j=0; j<150; j++) {
            gout << move_to(_x+i, _y+j) <<color(_bitmap[i][j],_bitmap[i][j],_bitmap[i][j]);
        }
    }
}
