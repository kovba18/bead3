#ifndef SZAMABR_HPP_INCLUDED
#define SZAMABR_HPP_INCLUDED

#include "Window.hpp"

const int gombmeret = 17;

class Szamabrazolo : public Widget {
public:
    class Gomb {
      protected:
        bool _irany;
        bool _nyomott=0;
        int _ex, _ey;

      public:
            Gomb(int ex, int ey, bool irany);
            bool selected(int mouse_x, int mouse_y, int _x, int _y);
            void draw(int _x, int _y);
            void press();
            void release();
      };

    Szamabrazolo(Window* window, int x, int y, int szam, int also, int felso);
    void handle(const genv::event &ev);
    void output();
    void draw();

protected:
    int _szam;
    int _also;
    int _felso;
    Gomb* fel;
    Gomb* le;
};

#endif // SZAMABR_HPP_INCLUDED
