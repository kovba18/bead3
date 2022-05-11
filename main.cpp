#include "menu.hpp"
#include "palya.hpp"
#include "mozgathatokep.hpp"
#include "szamabr.hpp"
#include "window.hpp"
#include <iostream>
#include <fstream>

using namespace genv;

class Content : public Window {
    public:
    Content() {
        gout<<color(135,135,135)<<move_to(0,0)<<box_to(XX-1,YY-1);
        //widgets.push_back(new Palya(this,100,50,0));
        //widgets.push_back(new Palya(this,100,400,0));
        widgets.push_back(new Mozgathatokep(this,30,30,0));
        widgets.push_back(new Mozgathatokep(this,60,30,1));
        widgets.push_back(new Mozgathatokep(this,90,30,2));
        widgets.push_back(new Mozgathatokep(this,120,30,3));
        widgets.push_back(new Mozgathatokep(this,150,30,4));
        gout<<refresh;
    }
};

void Window::beolvas() {
    std::ifstream befile("befile.txt");
        std::vector<std::vector<int>> hajo;
        int temp;
        char k;
        for (int i=0; i<150; i++) {
                std::vector<int> sor;
            for (int j=0; j<149; j++) {
                befile>>temp>>k;
                //betemp[j][i] = temp;
                sor.push_back(temp);
            }
            befile>>temp>>std::ws;
            sor.push_back(temp);
            //betemp[149][i] = temp;
            hajo.push_back(sor);
            if (i%30 == 29) {
                hajok.push_back(hajo);
                hajo.clear();
            }
        }
        //std::cout<<hajok.size()<<'\n';
}

void Window::changeVector(std::vector<std::vector<int>> &be, int id) {
    if (id < hajok.size()) be = hajok[id];
}

void Window::event_loop() {
    event ev;
    int focus = -1;

    while(gin >> ev) {
        if (ev.type == ev_mouse && ev.button == btn_left) {

        for (size_t i=0;i<widgets.size();i++) {
            if (widgets[i]->selected(ev.pos_x, ev.pos_y)) {focus=i; break;}
        }
        }

        if (focus > -1) {widgets[focus]->handle(ev);}
        gout<<move_to(30,30)<<color(100,130,200)<<box_to(330,330);
        for (size_t i=0; i< widgets.size(); i++) {
            widgets[i]->draw();
        }
        gout << refresh;
    }
}

int main() {
    gout.open(XX,YY);
    gout.load_font("LiberationSans-Regular.ttf", 20);
    Content* aktualis = new Content();
    aktualis->beolvas();

    aktualis->event_loop();

    return 0;
}
