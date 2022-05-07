#ifndef MOZGATHATOKEP_HPP_INCLUDED
#define MOZGATHATOKEP_HPP_INCLUDED

#include "Window.hpp"

class Mozgathatokep : public Widget {
public:
    Mozgathatokep(Window* window, int x, int y, int id, int bitmap[150][150]);
    void handle(const genv::event &ev);
    void output(){};
    void draw();

protected:
    int _rotation;
    int _id;
    bool _fogotte;
    int _mx;
    int _my;
    int _bitmap[150][150];
    std::vector <bool> _talalt;
};

#endif // MOZGATHATOKEP_HPP_INCLUDED
