#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "Window.hpp"

const int sebesseg = 3;

class Menu : public Widget {
public:
    class Listaelem {
        protected:
            std::string _szoveg;
            int _hossz;
        public:
            Listaelem(std::string szoveg, int hossz);
            std::string getstring() {return _szoveg;}
            bool selected(int mouse_x, int mouse_y, int _x, int _y);
    };

    Menu(Window* window, int x, int y, int maxhossz, std::vector<std::string> opciok);
    void handle(const genv::event &ev);
    void output();
    void draw();

protected:
    std::vector<Listaelem*> _lista;
    int _scroll = 0;
    int _magassag;
    int _kijelolt = -1;
    genv::canvas _menu;
};

#endif // MENU_HPP_INCLUDED
