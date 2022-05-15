#include "mozgathatokep.hpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace genv;

Sajatpalya::Mozgathatokep::Mozgathatokep(Sajatpalya* parent, int x, int y, int sizey, std::vector<std::vector<int>> bitmap) : _x(x), _y(y),_size_y(sizey), _bitmap(bitmap) {
    _size_x = 30;
    _rotated = 0;
    _parent = parent;
}

bool Sajatpalya::Mozgathatokep::selected(int mouse_x, int mouse_y) {
    if (_rotated) return (mouse_x > _x && mouse_x < _x + _size_y && mouse_y > _y && mouse_y < _y + _size_x);
    else return (mouse_x > _x && mouse_x < _x + _size_x && mouse_y > _y && mouse_y < _y + _size_y);
}


void Sajatpalya::Mozgathatokep::addtohajohelyek() {
    _parent->hajohelyek.push_back({(_x-_parent->_x)/30, (_y-_parent->_y)/30, _rotated, _size_y/30});
}

bool Sajatpalya::Mozgathatokep::foroghate() {
    if (_rotated) {
            if (_x+_size_x-_parent->_x-30 >=300 || _y+_size_y-_parent->_y >=300) return false;
    } else if (_x+_size_y-_parent->_x-30 >=300 || _y+_size_x-_parent->_y-30 >=300) return false;
    return true;
}

void Sajatpalya::Mozgathatokep::handle(const event &ev) {
    if (ev.type == ev_mouse) {
        if (selected(ev.pos_x, ev.pos_y) && ev.button == btn_left) {
            if (_held && _parent->meghiv()) _held=0; else _held = 1;
            mx = ev.pos_x - _x;
            my = ev.pos_y - _y;

        } else if (ev.button == btn_left && _held && _parent->meghiv()) _held = 0;

        if (_held) {
            if (_rotated) {
                if (ev.pos_x-mx > _parent->_x && ev.pos_x-mx+_size_y-30 < _parent->_x+_parent->_size_y) _x = _parent->_x+((ev.pos_x-mx-_parent->_x)/30) * 30;
                if (ev.pos_y-my > _parent->_y && ev.pos_y-my < _parent->_y+_parent->_size_x) _y = _parent->_y+((ev.pos_y-my-_parent->_y)/30)*30;
            } else {
                if (ev.pos_x-mx > _parent->_x && ev.pos_x-mx < _parent->_x+_parent->_size_x) _x = _parent->_x+((ev.pos_x-mx-_parent->_x)/30) * 30;
                if (ev.pos_y-my > _parent->_y && ev.pos_y-my+_size_y-30 < _parent->_y+_parent->_size_y) _y = _parent->_y+((ev.pos_y-my-_parent->_y)/30)*30;
            }
        }
    }
    if (ev.keycode == 'r' &&_held && foroghate()) {
        _rotated = (_rotated+1)%2;
        int temp = mx;
        mx = my;
        my = temp;
    }
}

Sajatpalya::Sajatpalya(Jatekmester* jatekmester, int x, int y) : Widget(jatekmester, x, y, 300,300) {
    _jatekmester->beolvas();
    std::vector<std::vector<int>> tempbitmap;
    _jatekmester->changeVector(tempbitmap, 0);
    hajok.push_back(new Mozgathatokep(this, _x, _y, 150, tempbitmap));
    _jatekmester->changeVector(tempbitmap, 1);
    hajok.push_back(new Mozgathatokep(this,_x+30, _y, 120, tempbitmap));
    _jatekmester->changeVector(tempbitmap, 2);
    hajok.push_back(new Mozgathatokep(this,_x+60, _y, 90, tempbitmap));
    _jatekmester->changeVector(tempbitmap, 3);
    hajok.push_back(new Mozgathatokep(this,_x+90, _y, 90, tempbitmap));
    _jatekmester->changeVector(tempbitmap, 4);
    hajok.push_back(new Mozgathatokep(this,_x+120, _y, 60, tempbitmap));
    meghiv();
}

void Sajatpalya::draw() {
    gout<<move_to(_x,_y)<<color(100,130,200)<<box_to(_x+_size_x,_y+_size_y);
    for (size_t i=0; i<hajok.size(); i++) {
        if (hajok[i]) hajok[i]->draw();
    }
}

void Sajatpalya::handle(const genv::event &ev) {
    for (size_t i=0; i<hajok.size(); i++) {
        if (hajok[i]->isheld()) {
            hajok[i]->handle(ev);
            return;
        }
    }

    for (size_t i=0; i<hajok.size(); i++) {
        hajok[i]->handle(ev);
    }

}

bool Sajatpalya::meghiv() {
    hajohelyek.clear();
    for (size_t i=0; i<hajok.size(); i++) {
        hajok[i]->addtohajohelyek();
    }
    return _jatekmester->Convertandcheck(this, helyek);
}

void Sajatpalya::Mozgathatokep::draw() {

    if (_rotated) {
        for (size_t j=0; j<_bitmap[0].size(); j++) {
            for (size_t i=0; i<_bitmap.size(); i++) {
                if (_bitmap[i][j] != 0) gout << move_to(_x+j, _y+i)<<color(_bitmap[i][j],_bitmap[i][j],_bitmap[i][j])<<dot;
            }
        }
    } else {
        for (size_t i=0; i<_bitmap.size(); i++) {
            for (size_t j=0; j<_bitmap[0].size(); j++) {
                if (_bitmap[i][j] != 0) gout << move_to(_x+i, _y+j)<<color(_bitmap[i][j],_bitmap[i][j],_bitmap[i][j])<<dot;
            }
        }
    }
}

void Sajatpalya::Mozgathatokep::canvasdraw(canvas& canv) {

    if (_rotated) {
        for (size_t j=0; j<_bitmap[0].size(); j++) {
            for (size_t i=0; i<_bitmap.size(); i++) {
                if (_bitmap[i][j] != 0) canv << move_to(_x-_parent->_x+j, _y-_parent->_y+i)<<color(_bitmap[i][j],_bitmap[i][j],_bitmap[i][j])<<dot;
            }
        }
    } else {
        for (size_t i=0; i<_bitmap.size(); i++) {
            for (size_t j=0; j<_bitmap[0].size(); j++) {
                if (_bitmap[i][j] != 0) canv << move_to(_x-_parent->_x+i, _y-_parent->_y+j)<<color(_bitmap[i][j],_bitmap[i][j],_bitmap[i][j])<<dot;
            }
        }
    }
}

void Sajatpalya::canvasrajzol(canvas& canv) {
    canv<<move_to(0,0)<<color(100,130,200)<<box_to(_size_x-1,_size_y-1);

    for (size_t i=0; i<hajok.size(); i++) {
        if (hajok[i]) hajok[i]->canvasdraw(canv);
    }
}

