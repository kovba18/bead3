#include "szamabr.hpp"
#include <sstream>

using namespace genv;

//A nested Gomb class functionjei
Szamabrazolo::Gomb::Gomb(int ex, int ey, bool irany) : _ex(ex), _ey(ey), _irany(irany){}

bool Szamabrazolo::Gomb::selected(int mouse_x, int mouse_y, int _x, int _y) {
    return (mouse_x > _x +_ex && mouse_x< _x+_ex + gombmeret*2 && mouse_y > _y + _ey && mouse_y < _y+_ey + gombmeret);
}

void Szamabrazolo::Gomb::draw(int _x, int _y) {
    if (_nyomott) gout<<color(0,255,0); else gout<<color(0,100,0);
    gout<<move_to(_x+_ex, _y+_ey)<<box_to(_x+_ex+gombmeret*2, _y+_ey+gombmeret);
}
void Szamabrazolo::Gomb::press() {
    _nyomott = 1;
}
void Szamabrazolo::Gomb::release() {
    _nyomott = 0;
}


Szamabrazolo::Szamabrazolo(Window* window, int x, int y, int szam, int also, int felso) : Widget(window, x, y), _szam(szam), _also(also), _felso(felso) {
    if (_szam > _felso || _szam < _also) _szam = rand() % _felso + _also;
    _size_x = 90;
    _size_y = 50;
    fel = new Szamabrazolo::Szamabrazolo::Gomb(50,5,1);
    le = new Szamabrazolo::Szamabrazolo::Gomb(50,27,1);
}


void Szamabrazolo::handle(const event &ev) {
    switch(ev.keycode) {
        case(key_up):
            if (_szam < _felso) _szam++;
        break;
        case(key_down):
            if (_szam > _also) _szam--;
        break;
        case(key_pgup):
            if (_szam+9 < _felso) _szam+=10; else _szam = _felso;
        break;
        case(key_pgdn):
            if (_szam-9 > _also) _szam-=10; else _szam = _also;
        break;
    }
    if (selected(ev.pos_x, ev.pos_y)) {
        if (fel->selected(ev.pos_x, ev.pos_y, _x, _y) && ev.button == btn_left) {
            if (_szam < _felso) _szam++;
            fel->press();
        } else if (le->selected(ev.pos_x, ev.pos_y, _x, _y) && ev.button == btn_left) {
            if (_szam > _also) _szam--;
            le->press();
        }
        if(ev.button == -btn_left)  {
            fel->release();
            le->release();
        }
    }
}

void Szamabrazolo::draw() {
    std::stringstream ss;
    ss<<_szam;
    gout << move_to(_x, _y) << color(200, 200, 200) << box(_size_x, _size_y)<< color(0, 0, 0) << move_to(_x + 4, _y) << text(ss.str());
    fel->draw(_x, _y);
    le->draw(_x, _y);
}
