#ifndef PALYA_HPP_INCLUDED
#define PALYA_HPP_INCLUDED

#include "Window.hpp"
#include "mozgathatokep.hpp"
#include <array>


class Palya : public Widget {
public:
    Palya(Jatekmester* jatekmester, int x, int y, std::function<void(bool a, int b)> asd);
    Palya(Jatekmester* jatekmester, int x, int y, std::array<std::array<int, 10>,10> hajok, canvas &canv, std::vector<std::array<int, 4>> poziciok, std::function<void(bool a, int b)> asd);
    void handle(const genv::event &ev);
    bool ellenoriz(int temp, int hajo, bool forgas);
    void draw();
    void lo(int id);
    void general();
    int gettalalt(int id) {return _tabla[id/10][id%10]->gettalalt();}
    int checksullyedt();

    class Selector {
        protected:
            int _ex, _ey;
            bool _hajovane;
            bool _lott = false;
            bool _hovered = false;
            Palya* _parent;
        public:
            Selector(int x, int y, bool hajovane, Palya* parent);
            void handle(const genv::event &ev) {};
            bool selected(int mouse_x, int mouse_y);
            void draw();
            void lo();
            bool getlott(){return _lott;}
            int gettalalt(){return _hajovane;}
    };

    protected:
        std::array<std::array<int, 10>,10> _hajok = {{0}};
        std::vector<std::array<int, 4>> _poziciok;
        std::function<void(bool a, int b)> _f;
        Selector* _tabla[10][10];
        genv::canvas _palyavaszon;
        bool _kie;
        int _sullyedt = 0;
};

#endif // PALYA_HPP_INCLUDED
