#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "widgets.hpp"
#include <vector>
#include <fstream>

const int XX = 500;
const int YY = 800;

class Window
{
protected:
    std::vector<Widget*> widgets;
    std::vector<std::vector<std::vector<int>>> hajok;

public:
    void event_loop();
    void changeVector(std::vector<std::vector<int>> &be, int id);
    void beolvas();
};


#endif // WINDOW_HPP_INCLUDED
