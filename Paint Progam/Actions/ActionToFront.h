#ifndef ACTION_TO_FRONT_H
#define ACTION_TO_FRONT_H

#include "Action.h"

//Add Bring to Front Action class
class ActionToFront : public Action
{
public:
	ActionToFront(ApplicationManager *pApp);

	virtual void Execute();

};

#endif