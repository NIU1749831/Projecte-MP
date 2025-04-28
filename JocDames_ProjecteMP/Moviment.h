#include "Posicio.h"

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
    Moviment() : m_desti("") {};

    /**
     * @brief Constructor amb parï¿½metres.
     * @param origen Posiciï¿½ d'origen del moviment.
     * @param desti Posiciï¿½ de destï¿½ del moviment.
     * @param pecesMortes Nombre de peces contrï¿½ries mortes en aquest moviment (opcional, per defecte 0).
     */
    Moviment(const Posicio& desti) : m_desti(desti) {};

    // Setters
    void setDesti(const Posicio& posicio) { m_desti = posicio; };
    

    //getters
    Posicio getDesti() const { return m_desti; };

 

private:
    Posicio m_desti;      // Posició de destí del moviment.
};
