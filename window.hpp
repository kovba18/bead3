#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "widgets.hpp"
#include <vector>
#include <fstream>
#include <array>

const int XX = 330;
const int YY = 730;

class Sajatpalya;

class Jatekmester
{
protected:
    std::vector<Widget*> widgets;
    std::vector<std::vector<std::vector<int>>> hajok;

public:
    void event_loop();
    void changeVector(std::vector<std::vector<int>> &be, int id);
    void jatekkezd();
    void korkezel();
    canvas& finalize(Sajatpalya* asd);
    bool Convertandcheck(Sajatpalya* asd, std::array<std::array<int, 10>,10> &eredeti);
    std::array<std::array<int, 10>,10> ConvertToMatrix(Sajatpalya* asd);
    void beolvas();
};


#endif // WINDOW_HPP_INCLUDED
