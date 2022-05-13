#ifndef PALYA_HPP_INCLUDED
#define PALYA_HPP_INCLUDED

#include "Window.hpp"
#include "mozgathatokep.hpp"
#include <array>


class Palya : public Widget {
public:
    Palya(Jatekmester* jatekmester, int x, int y);
    void handle(const genv::event &ev);
    bool ellenoriz(int temp, int hajo, bool forgas);
    void draw();
    void general();

    class Selector {
        protected:
            int _ex, _ey;
            bool _hajovane;
            bool _lott = false;
            bool _hovered = false;
        public:
            Selector(int x, int y, bool hajovane);
            void handle(const genv::event &ev) {};
            bool selected(int mouse_x, int mouse_y);
            void draw();
            void lo() {_lott = true;};
    };

    protected:
        int _meret = 10;
        int _hajok[10][10];
        std::vector<std::array<int, 3>> _poziciok;
        int talaltszam = 0; //ossz:17
        Selector* _tabla[10][10];
        canvas* _palyavaszon;
};

#endif // PALYA_HPP_INCLUDED
