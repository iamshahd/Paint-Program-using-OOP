#ifndef ACTION_SELECT_H
#define ACTION_SELECT_H

#include "Action.h"

//Add Exit Action class
class ActionSelect : public Action
{
public:
	ActionSelect(ApplicationManager *pApp);

	virtual void Execute();

};

#endif