#include "Moviment.h"

const int MAX_MOVIMENTS = 20; // M�xim de moviments v�lids per fitxa

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
    Fitxa();

    /**
     * @brief Constructor amb par�metres.
     * @param tipus Tipus de la fitxa.
     * @param color Color de la fitxa.
     * @param posicio Posici� inicial de la fitxa.
     */
    Fitxa(TipusFitxa tipus, int x, int y);

    // Setters
    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);
    void setPosicio(const Posicio& posicio);

    // Getters
    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    Posicio getPosicio() const;
    int getNumMovimentsValids() const;
    Moviment getMovimentValid(int index) const;

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
    bool afegirMovimentValid(const Moviment& moviment);

private:
    TipusFitxa m_tipus;                         // Tipus de la fitxa.
    ColorFitxa m_color;                         // Color de la fitxa.
    Posicio m_posicio;                          // Posicio actual de la fitxa.
    Moviment m_movimentsValids[MAX_MOVIMENTS];  // Llista de moviments valids.
    int m_numMovimentsValids;                    // Nombre de moviments valids actuals.
};
