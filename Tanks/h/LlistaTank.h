#include "IteradorNodeTank.h"

class LlistaTank
{
public:
    LlistaTank();
    ~LlistaTank();

    bool esBuida() const;
    IteradorNodeTank getInici() const;
	IteradorNodeTank getFinal() const;
	void setFinal(NodeTank* fin);
    IteradorNodeTank insereixNext(TankDolent t, IteradorNodeTank posicio);
    IteradorNodeTank eliminaNext(IteradorNodeTank posicio);
private:
    NodeTank* m_primer;
	NodeTank* m_ultim;
};