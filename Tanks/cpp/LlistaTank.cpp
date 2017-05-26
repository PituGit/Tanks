#include "../h/LlistaTank.h"

LlistaTank::LlistaTank()
{
    //ctor
    m_primer = NULL;
	m_ultim = NULL;
}

LlistaTank::~LlistaTank()
{
    //dtor
	while (m_primer != NULL)
		eliminaNext(NULL);
}

bool LlistaTank::esBuida() const
{
    return (m_primer == NULL);
}

IteradorNodeTank LlistaTank::getInici() const
{
    return IteradorNodeTank(m_primer);
}

IteradorNodeTank LlistaTank::getFinal() const
{
	return IteradorNodeTank(m_ultim);
}

void LlistaTank::setFinal(NodeTank* fin)
{
	m_ultim = fin;
}

IteradorNodeTank LlistaTank::insereixNext(TankDolent t, IteradorNodeTank posicio)
{
	NodeTank* aux = new NodeTank;
	if (aux != NULL)
	{
		aux->setValor(t);
		if (posicio.esNul())
		{
			aux->setNext(m_primer);
			m_primer = aux;
		}
		else
		{
			NodeTank* actual = posicio.getNode();
			aux->setNext(actual->getNext());
			actual->setNext(aux);
		}
	}
	return IteradorNodeTank(aux);
}

IteradorNodeTank LlistaTank::eliminaNext(IteradorNodeTank posicio)
{
 	NodeTank *aux;
	IteradorNodeTank seguent;
	if (posicio.esNul())
	{
		aux = m_primer;
		m_primer = aux->getNext();
		delete aux;
		seguent = IteradorNodeTank(m_primer);
	}
	else
	{
		aux = posicio.getNode()->getNext();
		if (aux != NULL)
        {
            posicio.getNode()->setNext(aux->getNext());
            seguent = IteradorNodeTank(aux->getNext());
            delete aux;
        }
	}
	return seguent;
}

