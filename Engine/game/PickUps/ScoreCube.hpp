#ifndef SCORECUBE_H
#define SCORECUBE_H

#include "PickUp.hpp"

class ScoreCube : public PickUp
{
public:
	ScoreCube();

	virtual void applyPickUp(Player* pPlayer);
private:

};

#endif