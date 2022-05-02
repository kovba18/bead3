#ifndef MOZGATHATOKEP_HPP_INCLUDED
#define MOZGATHATOKEP_HPP_INCLUDED

#include "Window.hpp"

class Mozgathatokep : public Widget {
public:
    Mozgathatokep(Window* window, int x, int y, int id, genv::canvas hatter);
    void handle(const genv::event &ev);
    void draw();

protected:
    int _rotation;
    int _id;
    bool _fogotte;
    int _mx;
    int _my;
    std::vector <bool> _talalt;
    genv::canvas _hatter;
};

#endif // MOZGATHATOKEP_HPP_INCLUDED
