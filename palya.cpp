#include "palya.hpp"
#include <cmath>

const int d=10;
const int r=10;

using namespace genv;

Palya::Selector::Selector(int x, int y, bool hajovane) : _ex(x), _ey(y), _hajovane(hajovane) {
    _red = 125+rand()% 20;
    _green = 196+rand()% 20;
    _blue = 225+rand()% 20;
}

bool Palya::Selector::selected(int mouse_x, int mouse_y) {
    return (mouse_x > _ex && mouse_x< _ex + 30*scale && mouse_y > _ey && mouse_y < _ey + 30*scale);
}

void Palya::Selector::draw() {
    gout<<color(_red, _green, _blue);
    gout<<move_to(_ex, _ey)<<box_to(_ex+30*scale-1, _ey+30*scale-1);
    if (_lott) {
		if (_hajovane) gout<<color(255,0,0); else gout<<color(255,255,255);
		for (int i=0; i<30; i++) {
            for (int j=0; j<30; j++) {
                if ((i-15)*(i-15)+(j-15)*(j-15) < d/2*d/2) gout<<move_to(i+_ex, j+_ey)<<dot;
            }
        }
	}
}

Palya::Palya(Window* window, int x, int y, bool kie) : Widget(window, x,y,10*30*scale, 10*30*scale), _kie(kie) {
    for (int i=0; i<_meret; i++) {
        for (int j=0; j<_meret; j++) {
            _tabla[i][j] = new Palya::Selector(_x+i*30*scale, _y+j*30*scale, rand()%2);
        }
    }
}

void Palya::handle(const genv::event &ev) {
    for (int i=0; i<_meret; i++) {
        for (int j=0; j<_meret; j++) {
            if (_tabla[i][j]->selected(ev.pos_x, ev.pos_y)) {
                if (ev.button == btn_left)_tabla[i][j]->lo();
            }
        }
    }
}


void Palya::draw() {
    gout << move_to(_x, _y) << color(200, 200, 200) << box(_size_x, _size_y);
    for (int i=0; i<_meret; i++) {
        for (int j=0; j<_meret; j++) {
            _tabla[i][j]->draw();
        }
    }
}
