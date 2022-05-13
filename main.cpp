#include "menu.hpp"
#include "palya.hpp"
#include "mozgathatokep.hpp"
#include "szamabr.hpp"
#include "window.hpp"
#include "button.hpp"
#include <iostream>
#include <fstream>
#include <functional>

using namespace genv;

class Content : public Jatekmester {
    public:
    Content() {
        gout<<color(135,135,135)<<move_to(0,0)<<box_to(XX-1,YY-1);
        //widgets.push_back(new Palya(this,15,YY-300-15));
        widgets.push_back(new Sajatpalya(this,15,15));
        widgets.push_back(new Button(this, "Kezdes", XX/2-50, 390, 100, 60, [this](){}));
        gout<<refresh;
    }
};

void Jatekmester::beolvas() {
    std::ifstream befile("befile.txt");
        std::vector<std::vector<int>> hajo;
        int temp;
        char k;
        for (int i=0; i<150; i++) {
                std::vector<int> sor;
            for (int j=0; j<149; j++) {
                befile>>temp>>k;
                sor.push_back(temp);
            }
            befile>>temp>>std::ws;
            sor.push_back(temp);
            hajo.push_back(sor);
            if (i%30 == 29) {
                hajok.push_back(hajo);
                hajo.clear();
            }
        }
}
void Jatekmester::jatekkezd() {
    widgets.push_back(new Palya(this,90,60));
}

canvas& Jatekmester::finalize(Sajatpalya* asd) {
canvas hatso;
hatso.open(300,300);
hatso<<move_to(0,0)<<color(100,130,200)<<box_to(300-1, 300-1);
asd->changecanvas(hatso);
asd->draw();
}
void Jatekmester::korkezel() {

}
bool Jatekmester::Convertandcheck(Sajatpalya* asd, std::array<std::array<int, 10>,10> &eredeti) {
    std::array<std::array<int, 10>,10> temp = {{0}};
    std::vector<std::array<int, 4>> helyek = asd->outputhajohelyek();

    int db = 0;
    for (size_t i=0; i<helyek.size(); i++) {
        for (int j=0; j<helyek[i][3]; j++) {
            temp[helyek[i][1]+j*abs(helyek[i][2]-1)][helyek[i][0]+j*helyek[i][2]] = 1;
        }
    }
    eredeti = temp;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) if (temp[i][j] == 1) db++;
    }
    std::cout<<db<<'\n';
    if (db!=17) std::cout<<"Szabalytalan elrendezes"<<'\n';
    return (db==17);
}


std::array<std::array<int, 10>,10> Jatekmester::ConvertToMatrix(Sajatpalya* asd) {
    std::array<std::array<int, 10>,10> temp = {{0}};
    std::vector<std::array<int, 4>> helyek = asd->outputhajohelyek();

    int db = 0;
    for (size_t i=0; i<helyek.size(); i++) {
        for (int j=0; j<helyek[i][3]; j++) {
            temp[helyek[i][1]+j*abs(helyek[i][2]-1)][helyek[i][0]+j*helyek[i][2]] = 1;
        }
    }
    return temp;
}

void Jatekmester::changeVector(std::vector<std::vector<int>> &be, int id) {
    if (id < hajok.size()) be = hajok[id];
}

void Jatekmester::event_loop() {
    event ev;
    int focus = -1;
    int stage = 0;
    for (size_t i=0; i< widgets.size(); i++) {
        widgets[i]->draw();
    }
    gout<<refresh;

    while(gin >> ev) {
    if (stage == 0) {
        if (ev.type == ev_mouse && ev.button == btn_left) {
            for (size_t i=0;i<widgets.size();i++) {
                if (widgets[i]->selected(ev.pos_x, ev.pos_y)) {focus=i; break;}
            }
        }
        if (focus > -1) {widgets[focus]->handle(ev);}
            for (size_t i=0; i< widgets.size(); i++) {
                widgets[i]->draw();
            }
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
