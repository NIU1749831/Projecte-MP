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
     * @brief Constructor amb par�metres.
     * @param origen Posici� d'origen del moviment.
     * @param desti Posici� de dest� del moviment.
     * @param pecesMortes Nombre de peces contr�ries mortes en aquest moviment (opcional, per defecte 0).
     */
    Moviment(const Posicio& desti) : m_desti(desti) {};

    // Setters
    void setDesti(const Posicio& posicio) { m_desti = posicio; };
    

    //getters
    Posicio getDesti() const { return m_desti; };

 

private:
    Posicio m_desti;      // Posici� de dest� del moviment.
};
