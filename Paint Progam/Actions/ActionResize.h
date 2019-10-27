#ifndef ACTION_RESIZE_H
#define ACTION_RESIZE_H

#include "Action.h"

//Add RESIZE Action class
class ActionResize : public Action
{
public:
	ActionResize(ApplicationManager *pApp);

	virtual void Execute();

};

#endif