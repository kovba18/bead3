#ifndef PALYA_HPP_INCLUDED
#define PALYA_HPP_INCLUDED

#include "Window.hpp"

const int scale = 1;

class Palya : public Widget {
public:
    Palya(Window* window, int x, int y, bool kie);
    void handle(const genv::event &ev);
    void output() {};
    void draw();

    class Selector {
        protected:
            int _ex, _ey;
            bool _hajovane;
            bool _lott = false;
            unsigned char _red;
            unsigned char _green;
            unsigned char _blue;
        public:
            Selector(int x, int y, bool hajovane);
            void handle(const genv::event &ev) {};
            bool selected(int mouse_x, int mouse_y);
            void draw();
            void lo() {_lott = true;};
    };

    protected:
        bool _kie;
        int _meret = 10;
        int _hajo[10][10];
        //std::vector<std::vector<Selector*>> _cellak;
        Selector* _tabla[10][10];
};

#endif // PALYA_HPP_INCLUDED
