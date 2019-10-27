#ifndef ACTION_TO_BACK_H
#define ACTION_TO_BACK_H

#include "Action.h"

//Add Send to Back Action class
class ActionToBack : public Action
{
public:
	ActionToBack(ApplicationManager *pApp);

	virtual void Execute();

};

#endif