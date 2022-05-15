#include "palya.hpp"
#include "mozgathatokep.hpp"
#include "window.hpp"
#include "button.hpp"
#include "textdisplay.hpp"
#include <fstream>
#include <functional>

using namespace genv;

class Content : public Jatekmester {
    public:
    Content() {
        jatekkezd();
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
    ellenfelloves=0;
    ellenfeltalalat=0;
    jatekosloves=0;
    jatekostalalat=0;
    gout<<color(135,135,135)<<move_to(0,0)<<box_to(XX-1,YY-1);
    widgets.clear();
    for (int i=0; i<100; i++) loheto[i] = i;
    Textdisplay * t1 = new Textdisplay(this, "Torpedo Jatek", 0, 20, 1, 30);
    Textdisplay * t2 = new Textdisplay(this, "Kovacs Balazs - BX700J 3. beadando", 0, 60, 1, 13);
    Textdisplay * t3 = new Textdisplay(this, "Helyezze el a flottajat a csata elott!", 0, 80, 1, 13);
    Sajatpalya * s1 = new Sajatpalya(this,15,215);
    Button* b1 = new Button(this, "Kezdes", XX/2-60, 550, 120, 60, [this, s1](){finalize(s1);});
}

void Jatekmester::finalize(Sajatpalya* asd) {
    canvas hatso;
    hatso.open(300,300);
    asd->canvasrajzol(hatso);
    std::array<std::array<int, 10>,10> temp = asd->outputhelyek();
    widgets.clear();

    gout<<color(135,135,135)<<move_to(0,0)<<box_to(XX-1,YY-1);
    Palya* p2 = new Palya(this,15,YY-300-15, temp, hatso, asd->outputhajohelyek(), [](bool asd, int b){});
    Palya* p1 = new Palya(this,15,15, [this, p2](bool asd, int b){korkezel(p2,asd,b);});

    Textdisplay * t1 = new Textdisplay(this, "Jatekos", 15, 15+300+22, 0, 15);
    result1 = new Textdisplay(this, "0/0", 0, 15+300+22, 1, 15);
    sullyedt1 = new Textdisplay(this, "0 sullyedt", 100, 15+300+22, 1, 15);

    Textdisplay * t2 = new Textdisplay(this, "Szamitogep", 15, 15+300+15+37, 0, 15);
    result2 = new Textdisplay(this, "0/0", 0, 15+300+15+37, 1, 15);
    sullyedt2 = new Textdisplay(this, "0 sullyedt", 100, 15+300+15+37, 1, 15);
}

void Jatekmester::korkezel(Palya* egyik, bool talalte, int sullyedt) {
    int temp = rand()% (100-jatekosloves);

    egyik->lo(loheto[temp]);
    jatekostalalat+=talalte;
    jatekosloves++;
    ellenfeltalalat+=egyik->gettalalt(loheto[temp]);
    ellenfelloves++;
    result1->talaltlott(jatekostalalat,jatekosloves);
    result2->talaltlott(ellenfeltalalat,ellenfelloves);

    sullyedt1->sullyedt(sullyedt);
    sullyedt2->sullyedt(egyik->checksullyedt());

    loheto[temp] = loheto[100-jatekosloves];
}

void Jatekmester::splashscreen(bool ki) {
    gout<<move_to(12,YY/2-58)<<color(255,255,255)<<box_to(XX-12,YY/2+58);
    gout<<move_to(20,YY/2-50)<<color(100,100,100)<<box_to(XX-20,YY/2+50);
    std::string szoveg;
    if (ki) szoveg = "Dicsoseges gyozelem!"; else szoveg = "Megsemmisito vereseg..";
    Textdisplay * fin = new Textdisplay(this, szoveg, 0, 15+300+25, 1, 18);
    Textdisplay * finguide = new Textdisplay(this, "A SPACE megnyomasaval a jatek ujraindul", 0, 15+300+50, 1, 10);
    fin->draw();
    finguide->draw();
    gout<<refresh;
}

bool Jatekmester::Convertandcheck(Sajatpalya* asd, std::array<std::array<int, 10>,10> &eredeti) {
    std::array<std::array<int, 10>,10> temp = {{0}};
    std::vector<std::array<int, 4>> helyek = asd->outputhajohelyek();

    int db = 0;
    for (size_t i=0; i<helyek.size(); i++) {
        for (int j=0; j<helyek[i][3]; j++) {
            temp[helyek[i][0]+j*helyek[i][2]][helyek[i][1]+j*abs(helyek[i][2]-1)] = 1;
        }
    }
    eredeti = temp;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) if (temp[i][j] == 1) db++;
    }
    if (db!=17) std::cout<<"Helytelen elrendezes"<<'\n';
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
    for (size_t i=0; i< widgets.size(); i++) {
        widgets[i]->draw();
    }
    gout<<refresh;

    while(gin >> ev && ev.keycode != key_escape) {
        if (ellenfeltalalat != 17 && jatekostalalat != 17) {
            if (ev.type == ev_mouse && ev.button == btn_left) {
                for (size_t i=0;i<widgets.size();i++) {
                    if (widgets[i]->selected(ev.pos_x, ev.pos_y)) {focus=i; break;}
                }
            }
            gout<<color(135,135,135)<<move_to(0,0)<<box_to(XX-1,YY-1);
            if (focus > -1) {widgets[focus]->handle(ev);}
                for (size_t i=0; i< widgets.size(); i++) {
                    widgets[i]->draw();
                }
            if (ellenfeltalalat == 17) splashscreen(0); else if (jatekostalalat == 17) splashscreen(1);
            gout << refresh;
        } else if (ev.keycode == key_space) jatekkezd();
    }
}

int main() {
    gout.open(XX,YY);
    Content* aktualis = new Content();
    aktualis->beolvas();

    aktualis->event_loop();

    return 0;
}
