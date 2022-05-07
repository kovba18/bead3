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
        std::ifstream befile("befile.txt");
        canvas hatso;
        hatso.open(150*4,150);
        int bemenet[150][150];
        int temp;
        char k;
        gout<<color(135,206,235)<<move_to(0,0)<<box_to(XX-1,YY-1);
        for (int i=0; i<30; i++) {
            for (int j=0; j<149; j++) {
                befile>>temp>>k;
                bemenet[i][j] = temp;
                if (bemenet[i][j] != 0) {
                    gout<<move_to(j, i)<<color(bemenet[i][j],bemenet[i][j],bemenet[i][j])<<dot;
                    //gout<<move_to(300-i, j)<<color(bemenet[i][j],bemenet[i][j],bemenet[i][j])<<dot;
                    //gout<<move_to(450-j, 150-i)<<color(bemenet[i][j],bemenet[i][j],bemenet[i][j])<<dot;
                    //gout<<move_to(450+i, 150-j)<<color(bemenet[i][j],bemenet[i][j],bemenet[i][j])<<dot;
                }
            }

            befile>>temp>>std::ws;
            bemenet[i][149] = temp;

        }
        gout<<refresh;
        widgets.push_back(new Mozgathatokep(this,100,100,2,bemenet));
        widgets.push_back(new Palya(this,100,100,0));
    }

};

void Window::event_loop() {
    event ev;
    //gout<<color(135,206,235)<<move_to(0,0)<<box_to(XX-1,YY-1);
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

    aktualis->megnyit();
    aktualis->event_loop();
    aktualis->bezar();
    return 0;
}
