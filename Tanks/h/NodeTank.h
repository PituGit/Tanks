#include "Tank.h"

class NodeTank
{
public:
    NodeTank();
    ~NodeTank();

    NodeTank* getNext();
    TankDolent& getValor();
    void setValor(TankDolent& can);
    void setNext(NodeTank* seg);
private:
    TankDolent m_valor;
    NodeTank* m_next;
};