#include <iostream>
#include "fitxa.h"
#include "posicio.h"
#include "moviment.h"

using namespace std;

#define N_FILES = 8;
#define N_COLUMNES = 8;


class Tauler
{
public:
    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    void getPosicionsPossibles(cont Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    string toString() const;

private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];
}

