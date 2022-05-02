#include "menu.hpp"
#include "mozgathatokep.hpp"
#include "szamabr.hpp"
#include "window.hpp"
#include <iostream>

//Tisztelt Tanár Úr!

//Az alabbi file a masodik beadandom fofileja. A beadandohoz 8 db file tartozik, 4db .hpp es 4db .cpp file.
//Ezeket a feltoltott fileok kozott talalja.

//Kovács Balázs (kovba18)
//BX700J


using namespace genv;

class Content : public Window {
    public:
    Content() {
    //A Szamabrazolo constructor function parameterei: window*, x és y pozicio, kiirt szam, also es felso hatar
    widgets.push_back(new Szamabrazolo(this, 10, 10, 50, 0, 100));
    widgets.push_back(new Szamabrazolo(this, 110, 10, 30, 10, 300));

    //A Menu constructor function parameterei: window*, x és y pozicio, maximum ysize, az opciok egy string tipusu vectorban
    widgets.push_back(new Menu(this, 10,70,100,{"elso", "masodik", "harmadik", "negyedik", "otodik", "hatodik", "hetedik"}));
    widgets.push_back(new Menu(this, 170,70,100,{"Inkscape", "Blender", "Gimp", "Audacity"}));
    }
};

void Window::event_loop() {
    event ev;
    for (size_t i = 0; i< widgets.size(); i++) {
        widgets[i]->draw();
    }
    gout<< refresh;
    int focus = -1;

    while(gin >> ev) {
        if (ev.type == ev_mouse && ev.button == btn_left) {

        for (size_t i=0;i<widgets.size();i++) {
            if (widgets[i]->selected(ev.pos_x, ev.pos_y)) {focus=i; break;}
        }
        }

        if (focus > -1) {widgets[focus]->handle(ev);}
        for (size_t i=0; i< widgets.size(); i++) {
            widgets[i]->draw();
        }
        gout << refresh;
        if (ev.keycode == key_enter) {
                std::cout<<"log"<<'\n';
            for (size_t i=0; i< widgets.size(); i++) {
                widgets[i]->output();
            }
        }
    }
}

int main() {
    gout.open(XX,YY, false);
    gout.load_font("LiberationSans-Regular.ttf", 20);

    Content* aktualis = new Content();

    //A megnyit es a bezar function a logfile-t hozza letre/zarja be
    aktualis->megnyit();
    aktualis->event_loop();
    aktualis->bezar();
    return 0;
}
