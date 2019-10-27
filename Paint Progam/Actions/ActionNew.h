#ifndef ACTION_NEW_H
#define ACTION_NEW_H

#include "Action.h"

//Add Action class
class ActionNew : public Action
{
public:
	ActionNew(ApplicationManager *pApp);

	//Add to the ApplicationManager
	virtual void Execute();

};

#endif