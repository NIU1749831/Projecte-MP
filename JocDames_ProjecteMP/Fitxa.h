#include "Moviment.h"

/**
 * @enum TipusFitxas
 * @brief Tipus de fitxa possible al joc de dames.
 */
typedef enum {
    TIPUS_NORMAL,   // Fitxa normal.
    TIPUS_DAMA,     // Dama.
    TIPUS_EMPTY     // Casella buida.
} TipusFitxa;

/**
 * @enum ColorFitxa
 * @brief Color possible d'una fitxa.
 */
typedef enum {
    COLOR_NEGRE,    // Fitxa negra.
    COLOR_BLANC     // Fitxa blanca.
} ColorFitxa;

class Fitxa {
public:
    // Constructors
    /**
     * @brief Constructor per defecte (crea una casella buida).
     */
    Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_BLANC), m_posicio("") 
    { 
        for (int i = 0; i < 11; i++)
            m_movimentsValids[i].setDesti(Posicio());
    };

    /**
     * @brief Constructor amb par�metres.
     * @param tipus Tipus de la fitxa.
     * @param color Color de la fitxa.
     * @param posicio Posici� inicial de la fitxa.
     */
    Fitxa(TipusFitxa tipus, ColorFitxa color, Posicio posico, int numMovimentsValids, Moviment movimentsValids[10]);

    // Setters
    void setTipus(TipusFitxa tipus) { m_tipus = tipus; };
    void setColor(ColorFitxa color) { m_color = color; };
    void setPosicio(const Posicio& posicio) { m_posicio = posicio; };

    // Getters
    TipusFitxa getTipus() const { return m_tipus; };
    ColorFitxa getColor() const { return m_color; };
    Posicio getPosicio() const { return m_posicio; };
    int getNumMovimentsValids() const { return m_numMovimentsValids; };
    Moviment getMovimentValid(int index) const { return m_movimentsValids[index]; };

    // Funcionalitats
    /**
     * @brief Converteix la fitxa en una dama.
     */
    void convertirADama();

    /**
     * @brief Afegeix un moviment v�lid a la fitxa.
     * @param moviment Moviment v�lid a afegir.
     * @return Cert si s'ha afegit correctament, fals si no hi ha espai.
     */
    void afegirMovimentValid(const Moviment& moviment);


private:
    TipusFitxa m_tipus;                         // Tipus de la fitxa.
    ColorFitxa m_color;                         // Color de la fitxa.
    Posicio m_posicio;                          // Posicio actual de la fitxa.
    Moviment m_movimentsValids[10];  // Llista de moviments valids.
    int m_numMovimentsValids;                    // Nombre de moviments valids actuals.
};
