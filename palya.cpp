#include "palya.hpp"
#include <cmath>
#include <iostream>

const int d=10;
const int r=10;

using namespace genv;

Palya::Selector::Selector(int x, int y, bool hajovane) : _ex(x), _ey(y), _hajovane(hajovane) {}

bool Palya::Selector::selected(int mouse_x, int mouse_y) {
    if (mouse_x > _ex && mouse_x< _ex + 30 && mouse_y > _ey && mouse_y < _ey + 30) {
        _hovered= true;
        return true;
    }
    _hovered = false;
    return false;
}

void Palya::Selector::draw() {
    gout<<color(140, 200, 200);
    if (_hovered) {
        gout<<color(255, 255, 255)<<move_to(_ex, _ey)<<box_to(_ex+29, _ey+29)
        <<color(140, 200, 200)<<move_to(_ex+3, _ey+3)<<box_to(_ex+29-3, _ey+29-3);
    } else {
    gout<<move_to(_ex, _ey)<<box_to(_ex+29, _ey+29);
    }
    if (_lott) {
		if (_hajovane) gout<<color(255,0,0); else gout<<color(255,255,255);
		for (int i=0; i<30; i++) {
            for (int j=0; j<30; j++) {
                if ((i-15)*(i-15)+(j-15)*(j-15) < d/2*d/2) gout<<move_to(i+_ex, j+_ey)<<dot;
            }
        }
	}
}


bool Palya::ellenoriz(int temp, int hajo, bool forg) {
    if (forg) {
        for (int j=0; j<hajo; j++) {
            if (temp+j*10 >= 100 || _hajok[(temp)/10+j][(temp)%10] != 0) return false;
        }
    } else {
        for (int j=0; j<hajo; j++) {
            if (temp%10+j >= 10 || _hajok[(temp)/10][temp%10+j] != 0) return false;
        }
    }
    return true;
}

void Palya::general() {
    int hajok[5] = {5,4,3,3,2};
    int temp;
    int forg;
    for (int i=0; i<5; i++) {
        forg = rand() % 2;
        for (int k=99; k>=0; k--) {
            int lehet[100];
            for (int j=0; j<100; j++) {lehet[j]=j;}
            int id = rand() % k+1;
            temp = lehet[id];
            if (Palya::ellenoriz(temp,hajok[i],forg)) {
                for (int j=0; j<hajok[i]; j++) {_hajok[(temp)/10+j*forg][(temp)%10+j*abs(forg-1)] = 1;}
                _poziciok.push_back({temp/10,temp%10, forg});
                break;
            }
            lehet[id] = lehet[k];
        }
    }
}

Palya::Palya(Window* window, int x, int y, bool kie) : Widget(window, x,y,10*30, 10*30), _kie(kie) {
    //Mozgathatokep* elso = new Mozgathatokep(window, _x, _y, 0)
    general();
    for (int i=0; i<_meret; i++) {
        for (int j=0; j<_meret; j++) {
            _tabla[i][j] = new Palya::Selector(_x+i*30, _y+j*30, _hajok[i][j]);
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
