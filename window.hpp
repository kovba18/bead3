#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "widgets.hpp"
#include <vector>
#include <fstream>

const int XX = 800;
const int YY = 800;

class Window
{
protected:
    std::vector<Widget*> widgets;
    std::ofstream output;

public:
    void event_loop();
    void stringlog(std::string szoveg) {output<<"asd"<<'\n';}
    void intlog (int szam) {output<<szam<<'\n';}
    void megnyit() {output.open("log.txt");}
    void bezar() {output.close();}
};


#endif // WINDOW_HPP_INCLUDED
