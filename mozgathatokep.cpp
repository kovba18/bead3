#include "mozgathatokep.hpp"
#include <iostream>
#include <vector>

using namespace genv;

Mozgathatokep::Mozgathatokep(Window* window, int x, int y, int id) : Widget(window, x, y), _id(id) {
    _w->beolvas();
    _w->changeVector(_bitmap, _id);
    _size_x = 30;
    _size_y = _bitmap[0].size();
    if (_id == 0) _size_y = 150;
}

void Mozgathatokep::handle(const event &ev) {
    if (ev.type == ev_mouse) {
        if (selected(ev.pos_x, ev.pos_y) && ev.button == btn_left) {
            if (_held) _held=0; else _held = 1;
            mx = ev.pos_x - _x;
            my = ev.pos_y - _y;
        } else if (ev.button == btn_left) _held = 0;

        if (_held) {
            _x = ((ev.pos_x-mx)/30) * 30;
            _y = ((ev.pos_y-my)/30)*30;
        }
    }
    if (ev.keycode == key_right) {
        _rotated = (_rotated+1)%2;
        int temp = mx;
        mx = my;
        my = temp;
        temp = _size_x;
        _size_x = _size_y;
        _size_y = temp;
    }

}

void Mozgathatokep::draw() {
    //gout<<move_to(30,30)<<color(100,130,200)<<box_to(330,330);
    if (_rotated) {
        for (int j=0; j<_size_x; j++) {
            for (int i=0; i<_size_y; i++) {
                if (_bitmap[i][j] != 0) gout << move_to(_x+j, _y+i)<<color(_bitmap[i][j],_bitmap[i][j],_bitmap[i][j])<<dot;
            }
        }
    } else {
        for (int i=0; i<_size_x; i++) {
            for (int j=0; j<_size_y; j++) {
                if (_bitmap[i][j] != 0) gout << move_to(_x+i, _y+j)<<color(_bitmap[i][j],_bitmap[i][j],_bitmap[i][j])<<dot;
            }
        }
    }
}
