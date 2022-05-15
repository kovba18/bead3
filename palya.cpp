#include "palya.hpp"
#include <cmath>
#include <iostream>

using namespace genv;

Palya::Selector::Selector(int x, int y, bool hajovane, Palya* parent) : _ex(x), _ey(y), _hajovane(hajovane), _parent(parent) {}

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
    if (_hovered) gout<<color(140, 200, 200)<<move_to(_ex, _ey)<<box_to(_ex+29, _ey+29);
    if (_lott) {
		if (_hajovane) gout<<color(255,0,0); else gout<<color(255,255,255);
		for (int i=0; i<30; i++) {
            for (int j=0; j<30; j++) if ((i-15)*(i-15)+(j-15)*(j-15) < 22) gout<<move_to(i+_ex, j+_ey)<<dot;
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
                _poziciok.push_back({temp/10,temp%10, forg, hajok[i]});
                break;
            }
            lehet[id] = lehet[k];
        }
    }
}

Palya::Palya(Jatekmester* jatekmester, int x, int y, std::array<std::array<int, 10>,10> hajok, canvas &canv, std::vector<std::array<int, 4>> poziciok, std::function<void(bool asd, int b)> asd) : Widget(jatekmester, x,y,10*30, 10*30), _hajok(hajok), _palyavaszon(canv), _poziciok(poziciok), _f(asd) {
    _kie = true;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            _tabla[i][j] = new Palya::Selector(_x+i*30, _y+j*30, _hajok[i][j], this);
        }
    }
}

Palya::Palya(Jatekmester* jatekmester, int x, int y, std::function<void(bool asd, int b)> asd) : Widget(jatekmester, x,y,10*30, 10*30), _f(asd) {
    _kie = false;
    general();
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            _tabla[i][j] = new Palya::Selector(_x+i*30, _y+j*30, _hajok[i][j],this);
        }
    }
}

int Palya::checksullyedt() {
    int db=0;
    _sullyedt=0;
    for (size_t i=0; i<_poziciok.size(); i++) {
        for (int j=0; j<_poziciok[i][3]; j++) {
            if (_hajok[_poziciok[i][0]+j*_poziciok[i][2]][_poziciok[i][1]+j*abs(_poziciok[i][2]-1)] == _tabla[_poziciok[i][0]+j*_poziciok[i][2]][_poziciok[i][1]+j*abs(_poziciok[i][2]-1)]->getlott()) db++;
        }
        if (db == _poziciok[i][3]) _sullyedt++;
        db=0;
    }
    return _sullyedt;
}


void Palya::handle(const genv::event &ev) {
    if (!_kie) {
        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++) {
                if (_tabla[i][j]->selected(ev.pos_x, ev.pos_y)) {

                    if (ev.button == btn_left) _tabla[i][j]->lo();
                }
            }
        }
    }
}

void Palya::lo(int id) {
    _tabla[id/10][id%10]->lo();
}

void Palya::Selector::lo() {
    if (!_lott) _parent->_f(_hajovane, _parent->checksullyedt());
    _lott = true;
}


void Palya::draw() {
    if (_kie) gout<<stamp(_palyavaszon,0,0,300,300,_x,_y); else gout<<move_to(_x, _y)<<color(100,100,100)<<box_to(_x+_size_x, _y+_size_y);
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            _tabla[i][j]->draw();
        }
    }
}
