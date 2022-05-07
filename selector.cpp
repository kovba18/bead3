#include "palya.hpp"
#include <sstream>

using namespace genv;

Palya::Palya(Window* window, int x, int y, int meret) : Widget(window, x,y), _meret(meret) {

    for (int i=0; i<_meret; i++) {
            std::vector<Selector*> ujsor;
        for (int j=0; j<_meret; j++) {
            ujsor.push_back(new Selector(window, _x+i*scale, _y+j*scale, 0));
        }
    }
}

void Palya::draw() {
    std::stringstream ss;
    ss<<_szam;
    gout << move_to(_x, _y) << color(200, 200, 200) << box(_size_x, _size_y)<< color(0, 0, 0) << move_to(_x + 4, _y) << text(ss.str());
    fel->draw(_x, _y);
    le->draw(_x, _y);
}
