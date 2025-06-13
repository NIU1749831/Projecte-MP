
#ifndef MOVIMENT_H
#define MOVIMENT_H



#include "Posicio.hpp"
#include<vector>

typedef enum {
    MOVIMENT,
    MATAR,
    MATAR_ENCADENAT,
    MATAR_ENCADENAT_FINAL,
    MOVIMENT_EMPTY
} TipusMoviment;

class Moviment
{
public:
    Moviment() : m_origen(Posicio()), m_desti(Posicio()), m_tipusMoviment(MOVIMENT_EMPTY) {};

    Moviment(const Posicio& origen, const Posicio& desti) : m_origen (origen), m_desti(desti), m_tipusMoviment(MOVIMENT_EMPTY) 
    {
        m_camino.push_back(desti); // el destí sol si només és 1 pas
    };

    Moviment(const Posicio& origen, const Posicio& desti, const TipusMoviment& tipus) : m_origen (origen), m_desti(desti), m_tipusMoviment(tipus)
    {
        m_camino.push_back(desti);
    };

    // Setters
    void setDesti(const Posicio& posicio) { m_desti = posicio; };
    void setTipusMoviment(const TipusMoviment& t) { m_tipusMoviment = t; };

    void setCami(const std::vector<Posicio>& cami) { m_camino = cami; };
    void afegeixPosicioAlCamino(const Posicio& p) { m_camino.push_back(p); };

    void afegeixCaptura(const Posicio& p) { m_captures.push_back(p); };
    void setCaptures(vector<Posicio> caps) { m_captures = caps; };

    // Getters
    Posicio getDesti() const { return m_desti; };
    TipusMoviment getTipusMoviment() const { return m_tipusMoviment; };
    Posicio getOrigen()const { return m_origen; };
    vector<Posicio> getCami() const { return m_camino; };

    const vector<Posicio>& getCamino() const { return m_camino; };
    const vector<Posicio>& getCaptures() const { return m_captures; };

private:
    Posicio m_desti;
    Posicio m_origen;
    TipusMoviment m_tipusMoviment;
    vector<Posicio> m_camino;
    vector<Posicio> m_captures;
};

#endif