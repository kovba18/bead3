#ifndef MOZGATHATOKEP_HPP_INCLUDED
#define MOZGATHATOKEP_HPP_INCLUDED

#include "Window.hpp"

class Mozgathatokep : public Widget {
public:
    Mozgathatokep(Window* window, int x, int y, int id);
    void handle(const genv::event &ev);
    void draw();

protected:
    bool _rotated;
    bool _held;
    int mx, my;
    int _id;
    int _hol;
    std::vector<std::vector<int>> _bitmap;
};

#endif // MOZGATHATOKEP_HPP_INCLUDED
