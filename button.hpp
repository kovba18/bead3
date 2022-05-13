#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "Window.hpp"
#include <functional>

class Button : public Widget {
public:
    Button(Jatekmester* jatekmester, std::string display, int x, int y, int sizex, int sizey, std::function<void()>);
    void handle(const genv::event &ev);
    void output(){};
    void draw();

protected:
    bool _nyomott=0;
    std::function<void()> _f;
    std::string _felirat;
};

#endif // BUTTON_HPP_INCLUDED
