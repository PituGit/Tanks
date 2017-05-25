#include "NodeTank.h"

class IteradorNodeTank
{
public:
    IteradorNodeTank();
    IteradorNodeTank(NodeTank *posicio);
    ~IteradorNodeTank();

    void seguent();
    TankDolent& getElement();
    bool esNul() const;
    NodeTank *getNode() const;
private:
    NodeTank* m_posicio;
};
