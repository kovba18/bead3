#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "widgets.hpp"
#include <vector>
#include <fstream>
#include <array>
#include <functional>

const int XX = 330;
const int YY = 730;

class Sajatpalya;
class Palya;
class Textdisplay;

class Jatekmester
{
protected:
    std::vector<Widget*> widgets;
    std::vector<std::vector<std::vector<int>>> hajok;
    std::array<int,100> loheto;
    Textdisplay * result1;
    Textdisplay * result2;
    Textdisplay * sullyedt1;
    Textdisplay * sullyedt2;
    int ellenfeltalalat = 0;
    int jatekostalalat = 0;
    int ellenfelloves = 0;
    int jatekosloves = 0;

public:
    void event_loop();
    void changeVector(std::vector<std::vector<int>> &be, int id);
    void jatekkezd();
    void korkezel(Palya* egyik, bool talalte, int sullyedt);
    void widgetadd(Widget* ez){widgets.push_back(ez);}
    void finalize(Sajatpalya* asd);
    void splashscreen(bool ki);
    bool Convertandcheck(Sajatpalya* asd, std::array<std::array<int, 10>,10> &eredeti);
    std::array<std::array<int, 10>,10> ConvertToMatrix(Sajatpalya* asd);
    void beolvas();
};


#endif // WINDOW_HPP_INCLUDED
