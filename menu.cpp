#include "menu.hpp"
#include <string>
#include <cmath>
#include <iostream>
using namespace genv;

Menu::Listaelem::Listaelem(std::string szoveg, int hossz) : _szoveg(szoveg), _hossz(hossz) {}

bool Menu::Listaelem::selected(int mouse_x, int mouse_y, int _x, int _y) {
    return mouse_x > _x && mouse_x < _x + _hossz && mouse_y > _y && mouse_y < _y + gout.cascent();
}



Menu::Menu(Window* window, int x, int y, int maxhossz, std::vector<std::string> opciok) : Widget(window, x, y, maxhossz) {
    _size_x = 150;
    for (size_t i=0; i<opciok.size(); i++) {
        _lista.push_back(new Menu::Listaelem(opciok[i], _size_x-1));
    }

    _magassag = gout.cascent()*_lista.size();
    _menu.open(_size_x*2, _magassag+5);
    _menu.load_font("LiberationSans-Regular.ttf", 20);
    _menu<<move_to(0,0)<<color(120,120,120)<<box_to(_size_x-1, _magassag+4)<<move_to(_size_x, 0)<<color(210,210,210)<<box_to(_size_x*2-1, _magassag+4)<<color(0,0,0);

    for (size_t i=0; i<_lista.size(); i++) {
        _menu<<move_to(0, gout.cascent()*i) << text(_lista[i]->getstring())<<move_to(_size_x, gout.cascent()*i)<<text(_lista[i]->getstring());
    }
    _menu<<refresh;
}


void Menu::output() {
    if (_kijelolt >= 0) _w->stringlog(_lista[_kijelolt]->getstring());
}


void Menu::handle(const event &ev) {
    if (_magassag > _size_y) {
        if (ev.button == btn_wheelup && abs(_scroll) >= 2) _scroll-=sebesseg; else if (ev.button == btn_wheeldown && abs(_scroll) < _magassag+5 - _size_y) _scroll+=sebesseg;
    }
    std::cout<<_scroll<<'\n';
    if (selected(ev.pos_x, ev.pos_y) && ev.button == btn_left) {
        for (size_t i=0; i<_lista.size(); i++) {
            if (_lista[i]->selected(ev.pos_x, ev.pos_y, _x, _y-_scroll + gout.cascent()*i)) _kijelolt = i;
        }
    }
}

void Menu::draw(){
    gout<<color(120,120,120)<<move_to(_x, _y)<<box_to(_x+_size_x-1, _y+_size_y-1);
    gout<<stamp(_menu, 0,_scroll,_size_x,_size_y,_x,_y);
    int mag = gout.cascent();
    if (_kijelolt >= 0 && _scroll < (_kijelolt+1)*mag+5 && _kijelolt*mag-_scroll < _size_y) {
        if (_scroll > _kijelolt*mag) gout<<stamp(_menu, _size_x,_scroll-_kijelolt*mag + _kijelolt*mag,_size_x,mag+5-_scroll+_kijelolt*mag,_x,_y);
        else if ((_kijelolt+1)*mag-_scroll+5 > _size_y){
            gout<<stamp(_menu, _size_x,_kijelolt*mag,_size_x,mag+_size_y-(_kijelolt+1)*mag+_scroll,_x,_y+_kijelolt*mag-_scroll);
        } else gout<<stamp(_menu, _size_x,_kijelolt*mag,_size_x,mag+5,_x,_y+_kijelolt*mag-_scroll);
    }
}
