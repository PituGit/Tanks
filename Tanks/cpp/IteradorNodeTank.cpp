#include "../h/IteradorNodeTank.h"

IteradorNodeTank::IteradorNodeTank()
{
    m_posicio = NULL;
}

IteradorNodeTank::~IteradorNodeTank()
{
    //dtor
}

IteradorNodeTank::IteradorNodeTank(NodeTank *posicio)
{
    m_posicio = posicio;
}

void IteradorNodeTank::seguent()
{
    m_posicio = m_posicio->getNext();
}

TankDolent& IteradorNodeTank::getElement()
{
    return m_posicio->getValor();
}

bool IteradorNodeTank::esNul() const
{
    return m_posicio == NULL;
}

NodeTank *IteradorNodeTank::getNode() const
{
    return m_posicio;
}
