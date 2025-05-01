#include <iostream>
#include "Fitxa.h"


using namespace std;

#define N_FILES  8
#define N_COLUMNES  8


class Tauler
{
public:
    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    string toString() const;
    bool buscaMovimentsValidSimple(int i, int j, int direccio);
    void asigna(int i, int j);

private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];
};

