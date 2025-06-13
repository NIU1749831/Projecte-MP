#ifndef CUAMOVIMENTS_H
#define CUAMOVIMENTS_H

#include "Moviment.h"
using namespace std;

class NodeMoviments 
{
public:
    NodeMoviments() : m_valor(Moviment()), m_next(nullptr), m_previous(nullptr) {}

    // Getters
    NodeMoviments* getNext() const { return m_next; }
    NodeMoviments* getPrevious() const { return m_previous; }
    Moviment getValor() const { return m_valor; }

    // Setters
    void setNext(NodeMoviments* next) { if (next != nullptr) m_next = next; }
    void setPrevious(NodeMoviments* prev) { if(prev != nullptr) m_previous= prev; }
    void setValor(const Moviment& val) { m_valor = val; }

private:
    Moviment m_valor;
    NodeMoviments* m_next;
    NodeMoviments* m_previous;
};


class CuaMoviments 
{
public:
    CuaMoviments() : m_inici(nullptr), m_final(nullptr), m_size(0) {}
    ~CuaMoviments();

    int getSize() const { return m_size; }
    NodeMoviments* getInici() const { return m_inici; }

    void setSize(int size) { m_size = size; }

    void push(const Moviment& x);
    void pop();

private:
	NodeMoviments* m_inici;
	NodeMoviments* m_final;
	int m_size;
};

#endif