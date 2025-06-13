#include<vector>
#include "Moviment.h"
#include "GraphicManager.h"
#include "info_joc.hpp"

typedef enum {
    TIPUS_EMPTY, 
    TIPUS_NORMAL, 
    TIPUS_DAMA 
} TipusFitxa;
typedef enum { 
    COLOR_BLANC, 
    COLOR_NEGRE } 
ColorFitxa;

class Fitxa
{
public:
    Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_BLANC), m_numMovimentsValids(0) {};
    Fitxa(TipusFitxa tipus, Posicio posicio);

    void setTipus(TipusFitxa tipus) { m_tipus = tipus; };
    void setColor(ColorFitxa color) { m_color = color; };
    void setPosicio(const Posicio& posicio) { m_posicio = posicio; };
	void setMovimentsValids(const vector<Moviment>& moviments);

    TipusFitxa getTipus() const { return m_tipus; };
    ColorFitxa getColor() const { return m_color; };
    Posicio getPosicio() const { return m_posicio; }
    int getNumMovimentsValids() const { return m_numMovimentsValids; }
    Moviment getMovimentValid(int index) const { return m_movimentsValids[index]; };

    void convertirADama();
    void afegirMovimentValid(const Moviment& moviment);
    void netejarMoviments();
    void visualitza() const;

private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Posicio m_posicio;
    Moviment m_movimentsValids[20];
    int m_numMovimentsValids;
};
