#include "Posicio.h"

/*
@brief: nos permite saber que tipo de movimiento es
* tendra 3 valores: NORMAL, MATAR, MATAR_ENCADENAT, MOVIMENT_EMPTY
*/

typedef enum {
    MOVIMENT,
    MATAR,
    MATAR_ENCADENAT,
    MOVIMENT_EMPTY
}TipusMoviment;

/**
 * @class Moviment
 * @brief Classe que representa un moviment possible d'una fitxa al tauler de dames.
 *
 * Conte informacio sobre l'origen, desti, peces mortes i cami seguit durant el moviment.
 */
class Moviment
{
public:
    // Constructors
    /**
     * @brief Constructor per defecte.
     */
    Moviment() : m_desti(Posicio()), m_tipusMoviment(MOVIMENT_EMPTY) {};

    /**
     * @brief Constructor amb parï¿½metres.
     * @param origen Posiciï¿½ d'origen del moviment.
     * @param desti Posiciï¿½ de destï¿½ del moviment.
     * @param pecesMortes Nombre de peces contrï¿½ries mortes en aquest moviment (opcional, per defecte 0).
     */
    Moviment(const Posicio& desti, const TipusMoviment& tmov) : m_desti(desti), m_tipusMoviment(tmov) {};

    // Setters
    void setDesti(const Posicio& posicio) { m_desti = posicio; };
    void setTipusMoviemnt(const TipusMoviment& t) { m_tipusMoviment = t; };
    

    //getters
    Posicio getDesti() const { return m_desti; };
    TipusMoviment getTipusMoviemt() const { return m_tipusMoviment; };

 

private:
    Posicio m_desti;                 // Posició de destí del moviment.
    TipusMoviment m_tipusMoviment  
};
