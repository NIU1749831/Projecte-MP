#include "CuaMoviments.h"

CuaMoviments::~CuaMoviments()
{
    // Eliminem tots els nodes un per un
    while (m_size!=0) {
        pop();  // Ja tenim la funció pop implementada que allibera el primer node
    }

    // Per seguretat, deixem els punters i la mida a zero
    m_inici = nullptr;
}

void CuaMoviments::push(const Moviment& x)
{
    NodeMoviments* nouNode = new NodeMoviments();

    if (m_size==0) 
    {
        m_inici = nouNode;
        m_final = nouNode;
        m_inici->setValor(x);
    }
    else {
        m_final->setNext(nouNode);
        nouNode->setPrevious(m_final);
        m_final = nouNode;
        nouNode->setValor(x);
    }
    m_size++;
}
void CuaMoviments::pop()
{
    if (m_size != 0 && m_inici != nullptr && m_inici->getNext() != nullptr)
    {
        NodeMoviments* aux = m_inici;
        m_inici = m_inici->getNext();
        m_inici->setPrevious(nullptr);

        delete aux;
    }
}