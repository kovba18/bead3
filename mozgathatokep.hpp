#ifndef MOZGATHATOKEP_HPP_INCLUDED
#define MOZGATHATOKEP_HPP_INCLUDED

#include "Window.hpp"
#include <array>

class Sajatpalya : public Widget {
    public:
        class Mozgathatokep{
        public:
            Mozgathatokep(Sajatpalya* parent, int x, int y, int sizey, std::vector<std::vector<int>> bitmap);
            void handle(const genv::event &ev);
            void draw();
            bool isheld(){return _held;}
            void addtohajohelyek();
            bool selected(int mouse_x, int mouse_y);
            bool foroghate();

        protected:
            bool _rotated;
            bool _held;
            int mx, my;
            int _id;
            int _x, _y;
            int _size_x, _size_y;
            std::vector<std::vector<int>> _bitmap;
            Sajatpalya* _parent;
        };

        Sajatpalya(Jatekmester* jatekmester, int x, int y);
        void draw();
        bool meghiv();
        std::vector<std::array<int, 4>> outputhajohelyek(){return hajohelyek;}
        void handle(const genv::event &ev);
        void changecanvas(canvas& uj) {_canv = uj;}

    protected:
        std::array<std::array<int, 10>,10> helyek;
        std::vector<std::array<int, 4>> hajohelyek;
        std::vector<Mozgathatokep*> hajok;
        canvas& _canv = gout;
};

#endif // MOZGATHATOKEP_HPP_INCLUDED
