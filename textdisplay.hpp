#ifndef TEXTDISPLAY_HPP_INCLUDED
#define TEXTDISPLAY_HPP_INCLUDED

#include "window.hpp"

class Textdisplay : public Widget {
public:
    Textdisplay(Jatekmester* jatekmester, std::string display, int x, int y, bool rendezes, int fontsize);
    void handle(const genv::event &ev);
    void draw();
    void talaltlott(int value1, int value2);
    void sullyedt(int value1);

protected:
    bool _rendezes;
    int _fontsize;
    int _value1;
    int _value2;
    std::string _felirat;
};

#endif // TEXTDISPLAY_HPP_INCLUDED
