#include "../h/NodeTank.h"

NodeTank::NodeTank()
{
    //ctor
    m_next = NULL;
}

NodeTank::~NodeTank()
{
    //dtor
    m_next = NULL;
}

NodeTank* NodeTank::getNext()
{
    return m_next;
}

TankDolent& NodeTank::getValor()
{
    return m_valor;
}

void NodeTank::setValor(TankDolent& can)
{
    m_valor=can;
}

void NodeTank::setNext(NodeTank* seg)
{
    m_next = seg;
}
