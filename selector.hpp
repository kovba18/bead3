#ifndef SELECTOR_HPP_INCLUDED
#define SELECTOR_HPP_INCLUDED

#include "Window.hpp"

const int scale = 30;

class Selector : public Widget {

class Selector : public Widget {
public:
    Selector(int x, int y) {};
    void handle(const genv::event &ev);
    void output() {};
    void draw();
protected:
};

#endif // SELECTOR_HPP_INCLUDED
